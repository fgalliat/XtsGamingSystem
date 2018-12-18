import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;

import javax.imageio.ImageIO;

public class EspColorTransform {

    static int color565(int r, int g, int b) {

        // System.out.print("r=" + ((r & 0xF8) << 8) + " ");
        // System.out.print("g=" + ((g & 0xFC) << 3) + " ");
        // System.out.println("b=" + (b >> 3) + " ");

        // System.out.print("r=" + ((r & 0xF8)) + " ");
        // System.out.print("g=" + ((g & 0xFC)) + " ");
        // System.out.println("b=" + (b >> 3) + " ");

        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    static int color565toRGB(int c565) {
        int r = (c565 >> 8) & 0xF8;
        int g = (c565 >> 5) & 0xFC;
        int b = (c565) % 0x20;

        // System.out.print("r=" + r + " ");
        // System.out.print("g=" + g + " ");
        // System.out.println("b=" + b);

        b = b * 255 / 31;
        g = g * 255 / 252;
        r = r * 255 / 248;
        // System.out.print("r=" + r + " ");
        // System.out.print("g=" + g + " ");
        // System.out.println("b=" + b);

        return ((r & 0xFF) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    static void test(int r, int g, int b) {
        String hex = Integer.toHexString(color565(r, g, b));
        for (int i = hex.length(); i < 4; i++) {
            hex = "0" + hex;
        }
        System.out.println("0x" + hex.toUpperCase());
    }

    public static final int MODE_64K = 1;

    static void treatImage(String filename) throws Exception {
        File f = new File(filename);

        String outFname = f.getName().toUpperCase();
        outFname = outFname.substring(0, outFname.lastIndexOf("."));
        outFname += ".PCT";

        int mode = MODE_64K; // 64K picture

        System.out.println(outFname);
        PrintStream fout = new PrintStream(new FileOutputStream(new File("./data", outFname)));
        if (mode == MODE_64K) {
            // 40967 bytes for 160x128px 64K file -> 7 bytes header (64K + WW + HH)
            fout.print("64K");

            BufferedImage img = ImageIO.read(f);
            BufferedImage workingCopy = img;
            int wwidth = workingCopy.getWidth();
            int wheight = workingCopy.getHeight();

            if (img.getWidth() == 320) {
                // let as is, assumes 320x240
            } else if (img.getWidth() > 160) {
                wwidth = 160;
                wheight = 128;
                Image scaled = img.getScaledInstance(wwidth, wheight, Image.SCALE_SMOOTH);
                workingCopy = new BufferedImage(wwidth, wheight, BufferedImage.TYPE_INT_ARGB);
                workingCopy.getGraphics().drawImage(scaled, 0, 0, null);
            }

            fout.write((wwidth / 256));
            fout.write((wwidth % 256));

            fout.write((wheight / 256));
            fout.write((wheight % 256));

            int[] rgb = new int[wwidth * wheight];
            workingCopy.getRGB(0, 0, wwidth, wheight, rgb, 0, wwidth);

            int cpt = 0;
            for (int y = 0; y < wheight; y++) {
                for (int x = 0; x < wwidth; x++) {
                    int rp = rgb[(y * wwidth) + x];
                    int a = (rp >> 24) & 0xFF; // should always be 255
                    int r = (rp >> 16) & 0xFF;
                    int g = (rp >> 8) & 0xFF;
                    int b = (rp) & 0xFF;
                    int c64k = color565(r, g, b);

                    // transparent color managment
                    if (a == 0) {
                        // Cf TFT_eSPI code :
                        // #define TFT_TRANSPARENT 0x0120
                        c64k = 0x0120;
                    }

                    if (cpt == 0) {
                        System.out.println("-> " + a + ", " + r + ", " + g + ", " + b);
                        System.out.println(Integer.toHexString(c64k));
                    }

                    fout.write(c64k / 256);
                    fout.write(c64k % 256);

                    cpt++;
                }
            }

        }

        fout.flush();
        fout.close();

    }

    public static void main(String[] args) throws Exception {
        // test( 0,0,255 );
        // test( 128,128,128 );
        // test( 50,50,50 );
        // test( 128,128,128 );
        // test( 200,200,200 );

        int c565 = color565(255, 255, 255);
        System.out.println(c565);

        int rgb = color565toRGB(c565);
        System.out.println(rgb);

        if ( !false ) {
            if (args != null && args.length == 0) {
                // args = new String[] { "./images/boot.png" };
                // args = new String[] { "./images/GODSFNT.png" };
                args = new String[] { "./images/DRMARIO.png" };
            }

            if (args != null && args.length == 1) {
                treatImage(args[0]);
            }
        } else {
            int nesRgb[] =
            { 0x7C7C7C, 0x0000FC, 0x0000BC, 0x4428BC, 0x940084, 0xA80020, 0xA81000, 0x881400,
            0x503000, 0x007800, 0x006800, 0x005800, 0x004058, 0x000000, 0x000000, 0x000000,
            0xBCBCBC, 0x0078F8, 0x0058F8, 0x6844FC, 0xD800CC, 0xE40058, 0xF83800, 0xE45C10,
            0xAC7C00, 0x00B800, 0x00A800, 0x00A844, 0x008888, 0x000000, 0x000000, 0x000000,
            0xF8F8F8, 0x3CBCFC, 0x6888FC, 0x9878F8, 0xF878F8, 0xF85898, 0xF87858, 0xFCA044,
            0xF8B800, 0xB8F818, 0x58D854, 0x58F898, 0x00E8D8, 0x787878, 0x000000, 0x000000,
            0xFCFCFC, 0xA4E4FC, 0xB8B8F8, 0xD8B8F8, 0xF8B8F8, 0xF8A4C0, 0xF0D0B0, 0xFCE0A8,
            0xF8D878, 0xD8F878, 0xB8F8B8, 0xB8F8D8, 0x00FCFC, 0xF8D8F8, 0x000000, 0x000000 };

            System.out.println("u16 nesRgb[] = {");
            for (int i=0; i < nesRgb.length; i++) {
                int col32 = nesRgb[i];
                int col32R = (col32 >> 16) & 0xFF;
                int col32G = (col32 >> 8 ) & 0xFF;
                int col32B = (col32 >> 0) & 0xFF;

                // System.out.println("r="+ col32R +" g="+ col32G +" b="+col32B);
                c565 = color565(col32R, col32G, col32B);
                System.out.print(c565+", ");
                if ( i % 8 == (8-1) ) {
                    System.out.println();
                }
            }
            System.out.print("};");
        }
    }

}
