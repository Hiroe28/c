#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

#define MAX_STR_LENGTH 256
#define FIELD_COUNT 15 // フィールド数15を#define
#define OK 0
#define NG 1

// 課題1 郵便番号データ用の構造体
typedef struct {
    wchar_t wstr_local_gov_code[6];
    wchar_t wstr_old_postal_code[6];
    wchar_t wstr_postal_code[8];
    wchar_t wstr_prefecture_kana[MAX_STR_LENGTH];
    wchar_t wstr_city_kana[MAX_STR_LENGTH];
    wchar_t wstr_town_kana[MAX_STR_LENGTH];
    wchar_t wstr_prefecture_kanji[MAX_STR_LENGTH];
    wchar_t wstr_city_kanji[MAX_STR_LENGTH];
    wchar_t wstr_town_kanji[MAX_STR_LENGTH];
    int i4_multi_zip_code;
    int i4_koaza_startup;
    int i4_has_chome;
    int i4_multi_town;
    int i4_update_status;
    int i4_update_reason;
} PostalCode;

// 課題3 構造体へデータを格納する関数

int set_postal_code_line(wchar_t* wstr_line, PostalCode* pst_postal_code) {

    wchar_t* wstr_token;
    wchar_t* wstr_next_token = NULL;
    int i4_field_count = 0;

    wchar_t work_line[MAX_STR_LENGTH]; // 作業用の文字列バッファ

    // 引数チェック
    if (wstr_line == NULL || pst_postal_code == NULL) {
        return NG;
    }

    wcscpy(work_line, wstr_line);

    // 文字列の分割処理
    wstr_token = wcstok(work_line, L",", &wstr_next_token);
    while (wstr_token != NULL && i4_field_count < FIELD_COUNT) {
        switch (i4_field_count) {
        case 0:
            // 全国地方公共団体コード
            wcscpy(pst_postal_code->wstr_local_gov_code, wstr_token);
            break;
        case 1:
            // （旧）郵便番号（5桁）
            wcscpy(pst_postal_code->wstr_old_postal_code, wstr_token + 1);
            pst_postal_code->wstr_old_postal_code[wcslen(pst_postal_code->wstr_old_postal_code) - 1] = L'\0';
            break;
        case 2:
            // 郵便番号（7桁）
            wcscpy(pst_postal_code->wstr_postal_code, wstr_token + 1);
            pst_postal_code->wstr_postal_code[wcslen(pst_postal_code->wstr_postal_code) - 1] = L'\0';
            break;
        case 3:
            // 都道府県名（カタカナ）
            wcscpy(pst_postal_code->wstr_prefecture_kana, wstr_token + 1);
            pst_postal_code->wstr_prefecture_kana[wcslen(pst_postal_code->wstr_prefecture_kana) - 1] = L'\0';
            break;
        case 4:
            // 市区町村名（カタカナ）
            wcscpy(pst_postal_code->wstr_city_kana, wstr_token + 1);
            pst_postal_code->wstr_city_kana[wcslen(pst_postal_code->wstr_city_kana) - 1] = L'\0';
            break;
        case 5:
            // 町域名（カタカナ）
            wcscpy(pst_postal_code->wstr_town_kana, wstr_token + 1);
            pst_postal_code->wstr_town_kana[wcslen(pst_postal_code->wstr_town_kana) - 1] = L'\0';
            break;
        case 6:
            // 都道府県名（漢字）
            wcscpy(pst_postal_code->wstr_prefecture_kanji, wstr_token + 1);
            pst_postal_code->wstr_prefecture_kanji[wcslen(pst_postal_code->wstr_prefecture_kanji) - 1] = L'\0';
            break;
        case 7:
            // 市区町村名（漢字）
            wcscpy(pst_postal_code->wstr_city_kanji, wstr_token + 1);
            pst_postal_code->wstr_city_kanji[wcslen(pst_postal_code->wstr_city_kanji) - 1] = L'\0';
            break;
        case 8:
            // 町域名（漢字）
            wcscpy(pst_postal_code->wstr_town_kanji, wstr_token + 1);
            pst_postal_code->wstr_town_kanji[wcslen(pst_postal_code->wstr_town_kanji) - 1] = L'\0';
            break;
        case 9:
            // 一町域が二以上の郵便番号で表される場合の表示
            pst_postal_code->i4_multi_zip_code = _wtoi(wstr_token);
            break;
        case 10:
            // 小字毎に番地が起番されている町域の表示
            pst_postal_code->i4_koaza_startup = _wtoi(wstr_token);
            break;
        case 11:
            // 丁目を有する町域の場合の表示
            pst_postal_code->i4_has_chome = _wtoi(wstr_token);
            break;
        case 12:
            // 一つの郵便番号で二以上の町域を表す場合の表示
            pst_postal_code->i4_multi_town = _wtoi(wstr_token);
            break;
        case 13:
            // 更新の表示
            pst_postal_code->i4_update_status = _wtoi(wstr_token);
            break;
        case 14:
            // 変更理由
            pst_postal_code->i4_update_reason = _wtoi(wstr_token);
            break;
        }
        i4_field_count++;
        wstr_token = wcstok(NULL, L",", &wstr_next_token);
    }

    return 0;
}


// 郵便番号データを表示する関数
int print_postal_code(PostalCode* pst_postal_code) {
    if (pst_postal_code == NULL)
    {
        return NG;
    }
    wprintf(L"全国地方公共団体コード: %ls\n", pst_postal_code->wstr_local_gov_code);
    wprintf(L"（旧）郵便番号: %ls\n", pst_postal_code->wstr_old_postal_code);
    wprintf(L"郵便番号: %ls\n", pst_postal_code->wstr_postal_code);
    wprintf(L"都道府県名（カタカナ）: %ls\n", pst_postal_code->wstr_prefecture_kana);
    wprintf(L"市区町村名（カタカナ）: %ls\n", pst_postal_code->wstr_city_kana);
    wprintf(L"町域名（カタカナ）: %ls\n", pst_postal_code->wstr_town_kana);
    wprintf(L"都道府県名（漢字）: %ls\n", pst_postal_code->wstr_prefecture_kanji);
    wprintf(L"市区町村名（漢字）: %ls\n", pst_postal_code->wstr_city_kanji);
    wprintf(L"町域名（漢字）: %ls\n", pst_postal_code->wstr_town_kanji);
    wprintf(L"一町域が二以上の郵便番号で表される場合の表示: %d\n", pst_postal_code->i4_multi_zip_code);
    wprintf(L"小字毎に番地が起番されている町域の表示: %d\n", pst_postal_code->i4_koaza_startup);
    wprintf(L"丁目を有する町域の場合の表示: %d\n", pst_postal_code->i4_has_chome);
    wprintf(L"一つの郵便番号で二以上の町域を表す場合の表示: %d\n", pst_postal_code->i4_multi_town);
    wprintf(L"更新の表示: %d\n", pst_postal_code->i4_update_status);
    wprintf(L"変更理由: %d\n", pst_postal_code->i4_update_reason);
    wprintf(L"\n");
    return OK;
}

// 課題6 漢字住所を結合して表示する関数
int print_kanji_address(PostalCode* pst_postal_code) {
    int i4_ret = NG;

    if (pst_postal_code == NULL)
    {
        goto _EXIT;
    }
    //丁目を有しているかで表示方法を変える
    if (pst_postal_code->i4_has_chome != 0) {
        wprintf(L"%ls%ls%lsx丁目\n", pst_postal_code->wstr_prefecture_kanji, pst_postal_code->wstr_city_kanji, pst_postal_code->wstr_town_kanji);
    }
    else {
        wprintf(L"%ls%ls%ls\n", pst_postal_code->wstr_prefecture_kanji, pst_postal_code->wstr_city_kanji, pst_postal_code->wstr_town_kanji);
    }
    i4_ret = OK;
_EXIT:;

    return i4_ret;
}

//// 課題6 漢字住所を結合して表示する関数
//int print_kanji_address(PostalCode* pst_postal_code) {
//    if (pst_postal_code == NULL)
//    {
//        return NG;
//    }
//    wprintf(L"%ls%ls%ls", pst_postal_code->wstr_prefecture_kanji, pst_postal_code->wstr_city_kanji, pst_postal_code->wstr_town_kanji);
//    //丁目を有しているかで表示方法を変える
//    if (pst_postal_code->i4_has_chome != 0) {
//        //wprintf(L"%lsx丁目\n", pst_postal_code->wstr_prefecture_kanji, pst_postal_code->wstr_prefecture_kanji);
//        wcscat(pst_postal_code->wstr_prefecture_kanji, "x丁目\n");
//    }
//    return OK;
//}



int main() {
    int i4_ret = NG;
    FILE* fp = NULL;
    wchar_t wstr_line[MAX_STR_LENGTH];
    int current_line = 0;
    PostalCode st_postal_code[6] = { 0 };  // 6行分のデータを格納する配列
    int data_index = 0;  // 配列のインデックス

    // ロケールを設定
    setlocale(LC_ALL, "ja_JP.UTF-8");
    // コンソールの出力コードページをUTF-8に設定
    SetConsoleOutputCP(CP_UTF8);

    // 課題5の回答（ファイル読み込み処理）を記載
    fp = _wfopen(L"utf_ken_all.csv", L"r, ccs=UTF-8");
    while (fgetws(wstr_line, sizeof(wstr_line) / sizeof(wchar_t), fp) != NULL) {
        current_line++;

        switch (current_line) {
        case 5:
        case 6:
        case 9735:
        case 9736:
        case 17337:
        case 17338:
            set_postal_code_line(wstr_line, &st_postal_code[data_index]);
            print_postal_code(&st_postal_code[data_index]);
            data_index++;
            break;
        }
    }
    // 各データの漢字住所を表示
    for (int i = 0; i < 6; i++) {
        i4_ret = print_kanji_address(&st_postal_code[i]);
        if (i4_ret != OK) {
            wprintf(L"Error: データの表示に失敗しました。\n");
            goto EXIT;
        }
    }


    i4_ret = OK;
EXIT:
    if (fp != NULL) {
        fclose(fp);
    }
    return i4_ret;
}

