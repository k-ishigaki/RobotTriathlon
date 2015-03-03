/*
 * ラインセンサのインターフェース
 */

#include "MSSPModule.h"

/**
 * ラインの状態を示す定数．
 * ラインセンサの仕様によって値が異なるので注意．
 */
typedef enum {
	LINE_STATE_ON_LINE = 0,			// ライン上
	LINE_STATE_RIGHT_EDGE_DITECTED = 1,	// 右エッジ検出
	LINE_STATE_LEFT_EDGE_DITECTED = 2,	// 左エッジ検出
	LINE_STATE_BOTH_EDGE_DITECTED = 3,	// 丁字検出
} LineState;

typedef struct {
	/**
	 * ラインの状態を取得する．
	 * @return ラインの状態を表す定数
	 */
	LineState (*getLineState)(void);
	/**
	 * ラインの位置を取得する．
	 * LineState = LINE_STATE_ON_LINEの時のみ有効．
	 * @return -2048~2047のラインの位置を示す値．
	 */
	int (*getLineValue)(void);
} LineSensor;

/**
 * ラインセンサのコンストラクタ．
 * I2Cのインターフェースが必要．
 * @param I2CInterfaceへのポインタ
 */
LineSensor* getLineSensor(I2CInterface*);

