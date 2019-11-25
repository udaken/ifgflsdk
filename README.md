# ifgflsdk
GFL-SDK( https://www.xnview.com/en/GFL/index.php )で画像を展開するSusie Pluginです。  
保存APIには対応していません。

## 注意事項
- 実験的なソフトウェアです。不具合が多いかと思います。
- 各対応ファイルの動作確認はしていません。
- GFL SDK は長らく更新されていません。脆弱性があった場合、対応される可能性が低いです。

## ライセンス
### ifgflsdk
ifgflsdk 自体はオープンソース(MITライセンス)ですのでフリーに使用できます。  
無保証で、いかなる保証もありません。自己責任で使用してください。

### GFL-SDK
GFL-SDKはフリーウェアで、個人的な利用または教育的利用に限られます。  
> GFL SDK is provided as FREEWARE (NO Adware, NO Spyware) for private or educational use (including non-profit organizations).
> If you enjoy using GFL SDK, Don't hesitate to help the developer with a small donation. 

## 動作環境
- 32bit版(ifgflsdk.spi): Windows 7/8.1/10 (Windows XPでも動作すると思いますが、確認していません)  
動作確認には主にLeeyes,NeeViewで行っています。
- 64bit版(ifgflsdk.sph): Windows 7/8.1/10

## ダウンロード
下記からダウンロードしてください。
https://github.com/udaken/ifgflsdk/releases

## インストール方法
1. 使用しているSusie Pluginアプリケーションのプラグインフォルダにifgflsdk.spi (64bit版ではifgflsdk.sph)をコピーしてください。
2. https://www.xnview.com/en/GFL/index.php からGFL SDK Windows(GflSDK-win.zip)をダウンロードしてください。
3. GflSDK\libW\libgfl340.dll (64bit版ではGflSDK\lib64W\libgfl340.dll) を ifgflsdkと同じ場所にコピーしてください。

## アンインストール方法
ifgflsdk.spi(64bit版ではifgflsdk.sph), libgfl340.dllを削除してください。  
(レジストリは使用していないません。)

## Website
https://github.com/udaken/ifgflsdk  
バグなどの連絡は下記からお願いします。  
https://github.com/udaken/ifgflsdk/issues  

## 64bit版(sph)
APIは
http://toro.d.dooo.jp/slplugin.html
に従います。  
現時点ではテストしていません。

## TODO
- Unicode API対応。
- INIファイルで設定を変えられるようにする。

## 対応ファイル形式
GFL-SDK 3.40では下記のファイル形式に対応しているようですが、
すべてはテストしていません。

|          **Description**          |      **Extension**      |
| :-------------------------------: | :---------------------: |
|     Adobe Photoshop Document      |           psd           |
|            Alias Image            |      pix als alias      |
|             Amiga IFF             |         iff blk         |
|                BMF                |           bmf           |
|          Bob Ray-Tracer           |           bob           |
|        CALS Raster Goup 1         |        cal cals         |
|          Canon PowerShot          |           crw           |
|      Casio QV-10/100 Camera       |           cam           |
|   Chinon ES-1000 digital camera   |           cmt           |
|          Cloe Ray-tracer          |           clo           |
|          CompuServe GIF           |        gif giff         |
|          DKB Ray-tracer           |           dis           |
|                DPX                |           dpx           |
|   Deluxe Paint, Electronic Arts   |           lbm           |
|            Digital F/X            |        tdim graf        |
|      EPS Interchange Format       |           epi           |
|          Electric Image           |         ei eidi         |
| Encapsulated Postscript (Preview) |           eps           |
|       Explore (TDI) & Maya        |         tdi iff         |
|            Gimp Bitmap            |           xcf           |
|            Gimp Brush             |           gbr           |
|             Gimp Icon             |           ico           |
|           Gimp Pattern            |           pat           |
|           Image Magick            |        mif miff         |
|            Imaging Fax            |           g3n           |
|         Intergraph Format         |       itg cit rle       |
| Joint Photographic Experts Group  |   jpg jpeg jif jfif J   |
|        Jeff's Image Format        |           jif           |
|           Kodak Cineon            |         cin dpx         |
|    Kodak DC120 Digital Camera     |           kdc           |
|         Kodak DC25 Camera         |           k25           |
|          Kodak Photo CD           |           pcd           |
|        Konica Camera File         |           kqp           |
|         LucasFilm Format          |           lff           |
|          MTV Ray-tracer           |           mtv           |
|     Macintosh Quickdraw/Pict      |      pic pict pct       |
|            Mayura Draw            |           pdx           |
|     Multiple Network Graphics     |           mng           |
|            OS/2 Bitmap            |         bmp bga         |
|     Open Image Library Format     |           oil           |
|  PaintShopPro Browser Cache File  |           jbf           |
|        PaintShopPro Frame         |           pfr           |
|        PaintShopPro Image         |           psp           |
|         PaintShopPro Mask         |           msk           |
|       PaintShopPro Pattern        |           pat           |
|     PaintShopPro Picture Tube     |           tub           |
|       PaintShopPro Texture        |           tex           |
|            Palm Pilot             |           pdb           |
|               Pegs                |         pxa pxs         |
|         Photopaint Image          |           apx           |
|        Picture Gear Pocket        |           prc           |
|        Pixar picture file         |   pic pxr picio pixar   |
|              Pixibox              |           pxb           |
|          Portable Bitmap          |        pbm rpbm         |
|     Portable Document Format      |           pdf           |
|        Portable Greyscale         |        pgm rpgm         |
|          Portable Image           |        pnm rpnm         |
|     Portable Network Graphics     |           png           |
|          Portable Pixmap          |        ppm rppm         |
|            Postscript             |           ps            |
|          Psion Series 3           |           pic           |
|          Psion Series 5           |           mbm           |
|          Qrt Ray-tracer           |           qrt           |
|            Quantel VPB            |           vpb           |
|         Quicktime Picture         |        qtif qti         |
|             Rayshade              |           pic           |
|       Ricoh Digital Camera        |           j6i           |
|      SciTex Continuous Tone       |         sct sc          |
|        Seattle Film Works         |           sfw           |
|  Seattle Film Works multi-image   |           pwp           |
|          Sega SJ-1 DIGIO          |           sj1           |
|       Silicon Graphics RGB        |     rgb bw iris sgi     |
|         Softimage bitmap          |         pic si          |
|      Sony DSC-F1 Cyber-shot       |           pmp           |
|     Sony Playstation TIM PSX      |           tim           |
|          Sun Icon/Cursor          |     icon cursor pr      |
|         Sun Raster Images         | ras rast sun sr scr rs  |
|       Sun TAAC file format        |   iff vff suniff taac   |
|        Synthetic Universe         |        synu syn         |
|          TIFF Revision 6          |      tif tim tiff       |
|         TrueVision Targa          | tga pix bpx vda icb vst |
|         Utah Raster image         |           rle           |
|               Vista               |           vst           |
|         Vivid Ray-tracer          |           img           |
|       Wavefront Raster file       |         rla rlb         |
|             Webshots              |       wbc wbp wbz       |
|              Winfax               |         fxs fxo         |
|     Windows & Aldus Metafile      |           wmf           |
|          Windows Bitmap           |   bmp rle rl4 rl8 sys   |
|         Windows Clipboard         |           clp           |
|          Windows Cursor           |           cur           |
|            Windows DIB            |           dib           |
|     Windows Enhanced Metafile     |           emf           |
|           Windows Icon            |           ico           |
|     Wireless Bitmap (level 0)     |      wbmp wbm wap       |
|            X11 BitMap             |         xbm bm          |
|            X11 PixMap             |         xpm pm          |
|        XV Visual Schnauzer        |           p7            |
|    Zsoft Multi-page Paintbrush    |           dcx           |
|   Zsoft Publisher's Paintbrush    |       pcx pcc dcx       |
