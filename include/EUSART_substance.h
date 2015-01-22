/*
 * EUSARTモジュールの実体生成部
 * EUSARTモジュールを利用するヘッダファイルによってインクルードされる
 * 例外的に関数定義と変数定義が含まれるため、
 * 普通のソースコードからはインクルードしてはいけない
 */

// 間違ってインクルードしていたらエラーを出す
#ifndef USE_EUSART_SUBSTANCE
#error you must not include this file unless using EUSART substance
#endif

#include <xc.h>
#include "Hardware.h"

void reset() {

}
