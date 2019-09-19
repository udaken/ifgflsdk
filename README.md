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

|  **Description** | **Extension** |
|  :------: | :------: |
|  3DS Max thumbnail | max |
|  AAA logo | bpr |
|  ACE texture | ace |
|  ADEX | img, rle |
|  AIM Grey Scale | ima, im |
|  AIPD image | aipd |
|  ARF | arf |
|  AT&T Group 4 | att |
|  AT&T multigen | icn |
|  AVHRR Image | sst |
|  AVT RAW | raw |
|  AWD | awd |
|  Ability Photopaint Image | apx |
|  Access | g4, acc |
|  Aces200 | ace |
|  Acorn Sprite | acorn |
|  AdTech perfectfax | adt |
|  Adobe Illustrator | ai |
|  Adobe PhotoParade (images) | php |
|  Adobe Photoshop | psd |
|  Advanced Art Studio | ocp, art, pic |
|  AirNav | anv |
|  Album bébé | frm |
|  Alias Image File | pix, als, alias |
|  Alpha Microsystems BMP | bmp |
|  Amapi | 2d |
|  Amica Paint | ami, [b] |
|  Amiga IFF | iff, blk |
|  Amiga icon | info |
|  Amstrad Cpc Screen | cpc |
|  Analyze | avw |
|  Analyze-7 | img |
|  Andrew Toolkit raster object | atk |
|  Apollo HDRU | hdru, hdr, gn |
|  ArcInfo Binary | hdr |
|  Art Director | art |
|  Artisan | art |
|  Artist 64 | a64 |
|  Artrage | ptg |
|  Artweaver Document | awd |
|  Astronomical Research Network | arn |
|  Atari grafik | pcp |
|  Aurora | sim |
|  Auto F/X | afx |
|  AutoCAD DWG | dwg, dwt |
|  AutoCAD DXF | dxf |
|  Autocad CAD-Camera | img |
|  Autodesk Animator | fli, flc |
|  Autodesk QuickCAD thumbnail | cad |
|  Autodesk SKETCH thumbnail | skf |
|  Autodesk SketchUp component | skp, skb |
|  Autologic | gm, gm2, gm4 |
|  Award Bios Logo | epa |
|  Axialis Screensaver (images) | ssp |
|  B3D (images) | b3d |
|  BFLI | bfl, bfli, fli, flp, afl |
|  BIAS FringeProcessor | msk, img, raw, flt |
|  BLP textures | blp |
|  BMF | bmf |
|  BSB/KAP | kap |
|  BYU SIR | sir |
|  Bert's Coloring | bmg, ibg |
|  Bfx Bitware | bfx |
|  Bio-Rad confocal | pic |
|  Blazing Paddles | pi |
|  Bob Raytracer | bob |
|  Brender | pix |
|  Brooktrout 301 | brk, 301, brt |
|  Brother Fax | uni |
|  Buttonz & Tilez texture | til |
|  CALS Raster | cal, cals, gp4, mil |
|  CDU Paint | cdu |
|  CGM | cgm |
|  CImage | dsi |
|  CMU Window Manager | cmu |
|  CP8 256 Gray Scale | cp8 |
|  CSV | csv |
|  Calamus | cpi, crg |
|  Camera RAW | raw |
|  Canon EOS-1D Mark II RAW | cr2 |
|  Canon Navigator Fax | can |
|  Canon PowerShot | crw |
|  Cartes Michelin | big |
|  Casio QV-10/100 Camera | cam |
|  Casio RAW | bay, raw |
|  Chinon ES-1000 digital camera | cmt |
|  Cisco IP Phone | cip |
|  Cloe Ray-Tracer | clo, cloe |
|  ColoRIX | rix, sci, scx, sc? |
|  CompW | wlm |
|  CompuServe GIF | gif, giff |
|  Computer Eyes, Digital Vision | ce |
|  ComputerEyes Raw | ce1, ce2 |
|  Contax RAW | bay, raw |
|  Core IDC | idc |
|  Corel Draw Bitmap (preview) | cdr |
|  Corel Draw Pattern (preview) | pat |
|  Corel Flow (preview) | bmf |
|  Corel Metafile Exchange (preview) | cmx |
|  Corel PhotoPaint 6.0 | cpt |
|  CoverDesigner (images) | ncd |
|  CoverDesigner Template (images) | nct |
|  Crayola | art |
|  Creative PC-CAM RAW | bay, raw |
|  DBW Render |  |
|  DIV Game Studio Map | map |
|  DIV Game Studio Multi Map | fpg |
|  DKB Ray-Tracer | dis |
|  DNG | dng |
|  DPX | dpx |
|  Dali Raw | sd0, sd1, sd2 |
|  Datacopy | img |
|  Degas & Degas Elite | pi1, pc1, pi2, pc2, pi3, pc3, pi4, pi5, pi6 |
|  Deluxe Paint, Electronic Arts | lbm, ilbm |
|  Dicom | dcm, acr, dic, dicom, dc3 |
|  Digital F/X | tdim |
|  Digital Research (GEM Paint) | img |
|  Direct Draw Surface | dds |
|  Discorp CMP Image | cmp |
|  DjVu | djvu, djv, iw4 |
|  DolphinEd | dol |
|  Doodle Atari | doo |
|  Doodle C64 | dd |
|  Doodle C64 (Compressed) | jj |
|  Dr Halo | cut |
|  Draz Paint | drz |
|  EA Sports FSH | fsh |
|  EPS Interchange Format | epi, ept |
|  ERI-chan (Entis Rasterized Image) | eri |
|  ESM Software Pix | pix |
|  Ecchi | ecc |
|  Eclipse | tile |
|  Edmics | c4 |
|  Egg Paint | trp |
|  Electric Image | ei, eidi |
|  Embroidery | bmc |
|  Encapsulated Postscript | ps, eps |
|  Encapsulated Postscript(Preview) | eps |
|  Enhance Simplex | esm |
|  Enhanced Compressed Wavelet | ecw |
|  Epson RAW | erf |
|  Eroiica | eif |
|  Everex Everfax | efx, ef3 |
|  Explore (TDI) & Maya | iff, tdi |
|  FIF (Iterated System) | fif |
|  FIT | fit |
|  Face Painter | fpt |
|  Fast Piecewise-constant | pwc |
|  Fax Group 3 | g3, fax |
|  Fax man | fmf |
|  Faxable PCX | fcx |
|  Faxable TIFF | ftf |
|  Fenix Map | map |
|  Fenix Multi Map | fpg |
|  FileMagic | mag |
|  Flash Image | fi |
|  FlashCam Frame | ncy |
|  FlashPix Format | fpx |
|  Flexible Image Transport System | fts, fits, fit |
|  Foculus RAW | bay, raw |
|  Fontasy Grafik | bsg |
|  Fremont Fax96 | f96 |
|  Fugawi Map | fx3 |
|  Fuji S2 RAW | raf |
|  Fun Painter II | fp2, fun |
|  Fun Photor | fpr |
|  Fuzzy bitmap | fbm, cbm |
|  GRS16 | g16 |
|  Gamma Fax | gmf |
|  GeoPaint | geo |
|  Gfa Raytrace | sul |
|  GigaPaint Hi-res | gih |
|  GigaPaint Multi | gig |
|  Gimp Bitmap | xcf |
|  Gimp Brush | gbr |
|  Gimp Icon | ico |
|  Gimp Pattern | pat |
|  GoDot | 4bt, 4bit, clp |
|  GunPaint | gun, ifl |
|  HD Photo | wdp, hdp |
|  HDRI | hdr, hdri |
|  HF | hf |
|  HP-48/49 GROB | gro, grb |
|  HP-49 OpenFire | gro2, gro4 |
|  HPGL-2 | hp, hpg, hgl, plt, hpgl, hpgl2, gl2, prn, prt, spl |
|  HRU | hru |
|  HSI Raw | raw |
|  Half-Life Model | mdl |
|  Hasselblad RAW | 3fr |
|  Hayes JTFax | jtf |
|  Hemera Photo Image | hpi |
|  Hemera Thumbs | hta |
|  Heretic II MipMap | m8 |
|  Hi-Eddi | hed |
|  Hires C64 | hir, hbm |
|  Homeworld Texture | lif |
|  IBM Kips | kps |
|  IBM Printer Page Segment | pse |
|  IM5 (Visilog) | im5 |
|  IMNET Image | imt |
|  IOCA | ica, ioca, mod |
|  IPLab | ipl |
|  IPod thumb | ithmb |
|  ISS | iss |
|  IcoFX | ifx |
|  Icon Library | icl |
|  Imacon/Hasselblad RAW | fff |
|  Image Capture Board | icb |
|  Image Magick file | mif, miff |
|  Image Speeder | ish |
|  Image System (Hires) | ish |
|  Image System (Multicolor) | ism |
|  Image Systems RLC2 Graphic | rlc |
|  ImageLab | b&w, b_w |
|  ImagePro Sequence | seq |
|  Imaging Fax | g3n |
|  Imaging Technology | img |
|  Img Software Set | img |
|  Inshape | iim |
|  InterPaint (Hires) | iph |
|  InterPaint (Multicolor) | ipt |
|  Intergraph Format | itg, cit, rle |
|  Interleaf | iimg |
|  Iris CT | ct |
|  Iris Graphics | iris |
|  J Wavelet Image Codec | wic |
|  JBIG | jbg, bie, jbig |
|  JBIG-2 | jb2 |
|  JFIF based file | jb2 |
|  JPEG / JFIF | jpg, jpeg, jif, jfif, J, jpe |
|  JPEG 8BIM header (Mac) | jpg, jpeg, jif, jfif, J, jpe |
|  JPEG XR | jxr |
|  JPEG-2000 Code Stream | jpc |
|  JPEG-2000 JP2 File Format | jp2, j2k, jpx, jpf |
|  JPEG-LS | jls |
|  Jeff's Image Format | jif |
|  Jigsaw | jig |
|  Jovian VI | vi |
|  Jpeg Network Graphics | jng |
|  JustButtons animated bitmap | btn |
|  KONTRON | img |
|  Khoros Visualization Image file | vif, viff, xv |
|  KinuPix Skin | thb |
|  Kiss Cel | cel |
|  Koala Paint | koa, kla |
|  Koala Paint (Compressed) | gg |
|  Kodak Cineon | cin |
|  Kodak DC120 Digital Camera | kdc |
|  Kodak DC25 Camera | k25 |
|  Kodak Photo CD | pcd |
|  Kodak Pro Digital RAW | dcr |
|  Kofax Group 4 | kfx |
|  Kolor Raw Format | kro |
|  Konica Camera File | kqp |
|  LSS16 | lss, 16 |
|  LView Pro | lvp |
|  LaserData | lda |
|  Leaf RAW | mos |
|  Leica RAW | bay, raw |
|  Light Work Image | lwi |
|  LucasFilm Format | lff |
|  Lumena CEL | cel |
|  LuraDocument Format | ldf |
|  LuraDocument.jpm Format | jpm |
|  LuraWave Format | lwf |
|  LuraWave JPEG-2000 Code Stream | jpc |
|  LuraWave JPEG-2000 Format | jp2, j2k, jpx, jpf |
|  MAKIchan Graphics | mag |
|  MGI Photosuite Project (images) | pzp |
|  MGR bitmap | mgr |
|  MRC (Medical Research Council) | mrc |
|  MTV Ray-Tracer | mtv |
|  Mac Paint | mac, mpnt, macp, pntg, pnt, paint |
|  Mac icon | icns |
|  Macintosh Quickdraw/Pict | pic, pict, pict2, pct |
|  Mac OSX Resource | rsc, rsrc |
|  Maggi Hairstyles & Cosmetics | fff |
|  Male MRI | pd, t1, t2 |
|  Male Normal CT | fre |
|  Mamiya RAW | mef |
|  Marks Russel File | mrf |
|  Mavica | 411 |
|  Maw-Ware Textures | mtx |
|  Mayura Draw | pdx |
|  MegaPaint | bld |
|  Megalux Frame | frm |
|  Micro Dynamics MARS | pbt |
|  Micro Illustrator Uncompressed | mil |
|  Micrografx Picture Publisher 4.0 | pp4 |
|  Micrografx Picture Publisher 5.0 | pp5 |
|  Micron RAW | bay, raw |
|  Microsoft Image Composer | mic |
|  Microsoft Paint | msp |
|  Microtek Eyestar | img |
|  Mindjongg Format | ipg |
|  Minolta DiMAGE RAW | mrw |
|  Mobile FAX | rfa |
|  MonkeyCard | pdb |
|  MonkeyLogo | pdb |
|  MonkeyPhoto | mph |
|  MrSid | sid |
|  Msx 2 Screen | sc2 |
|  Multiple Network Graphics | mng |
|  NCR Image | ncr |
|  NIST ihdr | pct |
|  National Imagery Transmission F. | ntf, nitf |
|  NeoBook Cartoon | car |
|  Neochrome (ST & TT) | neo |
|  Neopaint Mask | npm |
|  Neopaint Stamp | stw |
|  NewsRoom | nsr, ph, bn |
|  Nifti | img |
|  Nikon RAW | nef |
|  Nokia Group Graphics | ngg |
|  Nokia Logo File | nlm |
|  Nokia OTA bitmap | otb |
|  Nokia Operator Logo | nol |
|  OAZ Fax | oaz, xfx |
|  OS/2 Bitmap | bmp, bga |
|  Olicom Fax | ofx |
|  Olympus RAW | orf |
|  Open Image Library Format | oil |
|  OpenEXR | exr |
|  Optigraphics | ctf |
|  Optigraphics Tiled | ttf |
|  Optocat | abs |
|  Oric Hires | hir |
|  Oric TAP | tap |
|  Os/2 Warp | bga |
|  PABX background | pix |
|  PAX | pax |
|  PC Paint / Pictor Page | pic, clp |
|  PCO | b16 |
|  PM | pm |
|  Page Control Language | pcl |
|  Paint Magic | pmg |
|  PaintShopPro Browser Cache File | jbf |
|  PaintShopPro Brush | pspbrush |
|  PaintShopPro Brush | jbr |
|  PaintShopPro Frame | pfr, pspframe |
|  PaintShopPro Image | psp, pspimage |
|  PaintShopPro Mask | pspmask |
|  PaintShopPro Mask | msk |
|  PaintShopPro Pattern | pat |
|  PaintShopPro Picture Tube | tub, psptube |
|  PaintShopPro Texture | tex |
|  Palm Pilot | pdb |
|  Panasonic DMC-LC1 RAW | srf |
|  Panasonic LX3 RAW | rw2 |
|  Panasonic RAW | bay, raw |
|  Pegs | pxs, pxa |
|  Pentax *ist D | pef |
|  Pfs Art Publisher | art |
|  Photo Deluxe | pdd, pdb |
|  Photo Filtre Studio | pfi |
|  PhotoFantasy Image | fsy |
|  PhotoFrame | frm |
|  PhotoStudio File | psf |
|  PhotoStudio Stamp | stm |
|  Photomatrix | cat |
|  Pic2 | p2 |
|  Picasso 64 | p64 |
|  Picture Gear Pocket | prc |
|  Picture It! | mix |
|  Pixar picture file | pic, pxr, picio, pixar |
|  Pixel Power Collage | ib7, i17, i18, if9 |
|  Pixia | pxa |
|  Pixibox | pxb |
|  Planetary Data System | pds, img |
|  Playback Bitmap Sequence | bms |
|  Pocket PC Bitmap | 2bp |
|  Pocket PC Themes (images) | tsk |
|  Polychrome Recursive Format | prf |
|  Portable Bitmap | pbm, rpbm, ppma |
|  Portable Document Format | pdf |
|  Portable Greyscale | pgm, rpgm |
|  Portable Image | pnm, rpnm, pbm, rpbm, pgm, rpgm, ppm, rppm |
|  Portable Network Graphics | png, apng |
|  Portable Pixmap | ppm, rppm |
|  Portfolio Graphics | pgf |
|  Portfolio Graphics Compressed | pgc |
|  Portrait | cvp |
|  Poser Bump | bum |
|  Postscript | ps, ps1, ps2, ps3, eps, prn |
|  PowerCard maker | crd |
|  PowerPoint (images) | pps |
|  PowerPoint Presentation (images) | ppt |
|  Print Master | pm |
|  Print Shop | psa, psb |
|  Printfox/Pagefox | bs, pg, gb |
|  Prism | cpa |
|  Prisms | pri |
|  Psion Series 3 Bitmap | pic |
|  Psion Series 5 Bitmap | mbm |
|  Punk Productions Picture | ppp |
|  Puzzle | pzl |
|  Q0 | q0, rgb |
|  Qdv (Random Dot Software) | qdv |
|  Qrt Ray-Tracer | qrt |
|  Quake Texture | wal |
|  Quantel VPB | vpb |
|  QuickTime Image Format | qtif, qti |
|  RAW DVR | raw |
|  RIPTerm Image | icn |
|  Radiance | rad, img, pic |
|  Rainbow Painter | rp |
|  Raw | raw, gry, grey |
|  Rawzor | rwz |
|  Rayshade | pic |
|  Red Storm File Format | rsb |
|  Ricoh Digital Camera | j6i |
|  Ricoh Fax | 001, ric |
|  Ricoh IS30 | pig |
|  Rm2K XYZ | xyz |
|  Rollei RAW | rdc, ia |
|  RoverShot RAW | bay, raw |
|  RunPaint (Multicolor) | rpm |
|  Saracen Paint | sar |
|  SBIG CCD camera ST-4 | st4 |
|  SBIG CCD camera ST-X | stx, st4, st5, st6, st7, st8 |
|  SciFax | sci |
|  SciTex Continuous Tone | sct, ct, ch |
|  Seattle Film Works | sfw |
|  Seattle Film Works multi-image | pwp, sfw |
|  SecretPhotos puzzle | xp0 |
|  Sega SJ-1 DIGIO | sj1 |
|  Sharp GPB | img |
|  Siemens Mobile | bmx |
|  SIF MICHEL-Soft | sif |
|  Sigma RAW | x3f |
|  Silicon Graphics RGB | rgb, rgba, bw, iris, sgi, int, inta |
|  Sinar RAW | cs1, sti |
|  Skantek | skn |
|  Slow Scan Television | hrz |
|  SmartDraw 6 template | sdt |
|  SmartFax | 1 |
|  SmoothMove Pan Viewer | pan |
|  Softimage | pic, si |
|  Solitaire Image Recorder | sir |
|  Sony DSC-F1 Cyber-shot | pmp |
|  Sony DSC-F828 RAW | srf |
|  Sony PS2 TIM | tm2 |
|  Sony Playstation TIM | tim |
|  Sony RAW | sr2, arw |
|  Spectrum 512 | spu |
|  Spectrum 512 (Compressed) | spc |
|  Spectrum 512 (Smooshed) | sps |
|  SPOT | dat |
|  SriSun | ssi |
|  Stad | pic, pac, seq |
|  Star Office Gallery | sdg |
|  Starbase | img |
|  Stardent AVS X | x, avs, mbfs, mbfavs |
|  Starlight Xpress SX 500x291 RAW |  |
|  Stereo Image | jps |
|  ST Micro RAW | bay, raw |
|  Structured Fax Format | sff |
|  Sun Icon/Cursor | icon, cursor, ico, pr |
|  Sun Rasterfile | ras, rast, sun, sr, scr, rs |
|  Sun TAAC file | iff, vff, suniff, taac |
|  Syberia texture | syj |
|  Synthetic Universe | syn, synu |
|  SVG | svg |
|  TG4 | tg4 |
|  TI Bitmap | 92i, 73i, 82i, 83i, 85i, 86i, 89i |
|  TIFF Revision 6 | tif, tim, tiff |
|  TMSat image | imi |
|  TRS 80 | hr |
|  TealPaint | pdb |
|  Teli Fax | mh |
|  Thumbnail | tnl |
|  TilePic | tjp |
|  Tiny | tny, tn1, tn2, tn3 |
|  TopDesign Thumbnail | b3d, b2d |
|  Total Annihilation | gaf |
|  Truevision Targa | tga, targa, pix, bpx, ivb |
|  Ulead Pattern | pst |
|  Ulead PhotoImpact | upi |
|  Ulead Texture (images) | pe4 |
|  Usenix FaceServer | fac, face |
|  Utah raster image | rle, urt |
|  VIPS Image | v |
|  VITec | vit |
|  VRML2 | wrl |
|  Venta Fax | vfx |
|  Verity | vif |
|  Vicar | vic, vicar, img |
|  Vidcom 64 | vid |
|  Video Display Adapter | vda |
|  Vista | vst |
|  Vivid Ray-Tracer | img |
|  Vort | pix |
|  Vue d'esprit | vob |
|  WAD (Half life) | wad |
|  WSQ | wsq |
|  WaveL | iwc |
|  Wavefront Raster file | rla, rlb, rpf |
|  WebShots (images) | wb1, wbc, wbp, wbz |
|  Weekly Puzzle | jig |
|  WebP | webp, wep |
|  Whypic | ypc |
|  WinFAX | fxs, fxo, wfx, fxr, fxd, fxm |
|  WinMIPS | pic |
|  Windows & Aldus Metafile | wmf |
|  Windows Animated Cursor | ani |
|  Windows Bitmap | bmp, rle, vga, rl4, rl8, sys |
|  Windows Clipboard | clp |
|  Windows Comp. Enhanced Metafile | emz |
|  Windows Compressed Metafile | wmz |
|  Windows Cursor | cur |
|  Windows DIB | dib |
|  Windows Enhanced Metafile | emf |
|  Windows Icon | ico |
|  Winzle Puzzle | wzl |
|  Wireless Bitmap (level 0) | wbmp, wbm, wap |
|  Word Perfect Graphics (images) | wpg |
|  Worldport Fax | wfx |
|  X Windows System dump | xwd, x11 |
|  X11 Bitmap | xbm, bm |
|  X11 Pixmap | xpm, pm |
|  XV Visual Schnauzer | p7 |
|  Xara (images) | xar |
|  Xerox DIFF | xif |
|  Ximage | xim |
|  Xionics SMP | smp |
|  YUV 16Bits | yuv, qtl, uyvy |
|  YUV 16Bits Interleaved | yuv, qtl, uyvy |
|  YUV 4:1:1 | yuv, qtl |
|  YUV 4:2:2 | yuv, qtl |
|  YUV 4:4:4 | yuv, qtl |
|  ZX Spectrum Hobetta | $s, $c, !s |
|  ZX Spectrum Snapshot | sna |
|  ZX Spectrum standard screen | scr |
|  ZZ Rough | rgh |
|  Zeiss BIVAS | dta |
|  Zeiss LSM | lsm |
|  Zoner Callisto Metafile (preview) | zmf |
|  Zoner Zebra Metafile (preview) | zbr |
|  Zsoft Multi-page Paintbrush | dcx |
|  Zsoft Publisher's Paintbrush | pcx, pcc, dcx |
|  byLight | bif |