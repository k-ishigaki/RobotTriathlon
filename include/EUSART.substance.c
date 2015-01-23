/*
 * EUSARTモジュールの実体生成部
 * EUSARTモジュールを利用するソースコードによってインクルードされる
 * 関数定義と変数定義が含まれるため、インクルードする場所には気をつける必要がある
 * 普通のソースコードからはインクルードしてはいけない
 */

// 普通のソースコードからはインクルードできないようにする
#ifdef USING_EUSART_SUBSTANCE

#include <xc.h>
#include "Hardware.h"

void reset() {

}

#endif
