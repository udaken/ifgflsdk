#pragma once

#include <cstdint>
#include <windows.h>

// Susie エラーコード
enum class SUSIE_RESULT
{
	NO_FUNCTION = -1, // その機能はインプリメントされていない
	ALL_RIGHT = 0, // 正常終了
	SPI_E_ABORT = 1, // コールバック関数が非0を返したので展開を中止した
	NOT_SUPPORT = 2, // 未知のフォーマット
	OUT_OF_ORDER = 3, // データが壊れている
	SPI_NO_MEMORY = 4, // メモリーが確保出来ない
	MEMORY_ERROR = 5, // メモリーエラー
	FILE_READ_ERROR = 6, // ファイルリードエラー
	SPI_WINDOW_ERROR = 7, // 窓が開けない (非公開のエラーコード)
	OTHER_ERROR = 8, // 内部エラー
	FILE_WRITE_ERROR = 9, // 書き込みエラー (非公開のエラーコード)
	SPI_END_OF_FILE = 10, // ファイル終端 (非公開のエラーコード)
};

// Susie 追加情報フラグ
enum class SUSIE_FLAG
{
	SPI_INPUT_MASK = 0b111,
	SPI_INPUT_FILE = 0b000, // 入力はディスクファイル
	SPI_INPUT_MEMORY = 0b001, // 入力はメモリ上のイメージ

	SPI_IGNORE_CASE = 0b10000000, // ファイル名の大文字小文字を同一視する

	SPI_OUTPUT_MASK   = 0b11100000000,
	SPI_OUTPUT_FILE   = 0b00000000000, // 出力はディスクファイル
	SPI_OUTPUT_MEMORY = 0b00100000000, // 出力はメモリ上のイメージ
};

typedef ULONG_PTR susie_time_t;
//-------------------------------------- DLL 構造体
#pragma pack(push,1)
typedef struct PictureInfo {
	long    left, top;	// 画像を展開する位置
	long    width;	// 画像の幅(pixel)
	long    height;	// 画像の高さ(pixel)
	WORD    x_density;	// 画素の水平方向密度
	WORD    y_density;	// 画素の垂直方向密度
	short   colorDepth;	// １画素当たりのbit数
#ifdef _WIN64
	char  dummy[2]; // アラインメント
#endif
	HLOCAL  hInfo;	// 画像内のテキスト情報
} SUSIE_PICTUREINFO;

typedef struct {
	unsigned char  method[8];	// 圧縮法の種類
	ULONG_PTR      position;	// ファイル上での位置
	ULONG_PTR      compsize;	// 圧縮されたサイズ
	ULONG_PTR      filesize;	// 元のファイルサイズ
	susie_time_t   timestamp;	// ファイルの更新日時
	char           path[200];	// 相対パス
	char           filename[200];	// ファイル名
	unsigned long  crc;	// CRC
#ifdef _WIN64
						// 64bit版の構造体サイズは444bytesですが、実際のサイズは
						// アラインメントにより448bytesになります。環境によりdummyが必要です。
	char        dummy[4];
#endif
} SUSIE_FINFO;

typedef struct {
	unsigned char  method[8];	// 圧縮法の種類
	ULONG_PTR      position;	// ファイル上での位置
	ULONG_PTR      compsize;	// 圧縮されたサイズ
	ULONG_PTR      filesize;	// 元のファイルサイズ
	susie_time_t   timestamp;	// ファイルの更新日時
	WCHAR          path[200];	// 相対パス
	WCHAR          filename[200];	// ファイルネーム
	unsigned long  crc;		// CRC
}SUSIE_FINFOW;
#pragma pack(pop)

extern "C"
{
	// コールバック
	typedef int(WINAPI *SUSIE_PROGRESS)(int32_t nNum, int32_t nDenom, LONG_PTR lData);

	int32_t WINAPI GetPluginInfo(int32_t infono, LPSTR  buf, int32_t buflen);
	int32_t WINAPI GetPluginInfoW(int32_t infono, LPWSTR buf, int32_t buflen);

	BOOL WINAPI IsSupported(LPCSTR  filename, void* dw);
	BOOL WINAPI IsSupportedW(LPCWSTR filename, void* dw);

	SUSIE_RESULT WINAPI GetPictureInfo(LPCSTR  buf, size_t len, SUSIE_FLAG flag, SUSIE_PICTUREINFO* lpInfo);
	SUSIE_RESULT WINAPI GetPictureInfoW(LPCWSTR buf, size_t len, SUSIE_FLAG flag, SUSIE_PICTUREINFO* lpInfo);

	SUSIE_RESULT WINAPI GetPicture(LPCSTR  buf, size_t len, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData);
	SUSIE_RESULT WINAPI GetPictureW(LPCWSTR buf, size_t len, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData);

	SUSIE_RESULT WINAPI GetPreview(LPCSTR  buf, size_t len, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData);
	SUSIE_RESULT WINAPI GetPreviewW(LPCWSTR buf, size_t len, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData);

	SUSIE_RESULT WINAPI GetArchiveInfo(LPCSTR  buf, size_t len, SUSIE_FLAG flag, HLOCAL* lphInf);
	SUSIE_RESULT WINAPI GetArchiveInfoW(LPCWSTR buf, size_t len, SUSIE_FLAG flag, HLOCAL* lphInf);

	SUSIE_RESULT WINAPI GetFileInfo(LPCSTR  buf, size_t len, LPCSTR  filename, SUSIE_FLAG flag, SUSIE_FINFO* lpInfo);
	SUSIE_RESULT WINAPI GetFileInfoW(LPCWSTR buf, size_t len, LPCWSTR filename, SUSIE_FLAG flag, SUSIE_FINFOW* lpInfo);

	SUSIE_RESULT WINAPI GetFile(LPCSTR  src, size_t len, LPSTR  dest, SUSIE_FLAG flag, SUSIE_PROGRESS progressCallback, intptr_t lData);
	SUSIE_RESULT WINAPI GetFileW(LPCWSTR src, size_t len, LPWSTR dest, SUSIE_FLAG flag, SUSIE_PROGRESS progressCallback, intptr_t lData);

	SUSIE_RESULT WINAPI ConfigurationDlg(HWND parent, int fnc);

	SUSIE_RESULT WINAPI CreatePicture(LPCSTR  filepath, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PICTUREINFO* lpInfo, SUSIE_PROGRESS progressCallback, intptr_t lData);
	SUSIE_RESULT WINAPI CreatePictureW(LPCWSTR filepath, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PICTUREINFO* lpInfo, SUSIE_PROGRESS progressCallback, intptr_t lData);
}
