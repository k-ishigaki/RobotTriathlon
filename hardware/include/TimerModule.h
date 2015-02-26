/*
 * タイマモジュールのインターフェース定義
 * どのようなインターフェースを定義すればよいか推敲中
 * とりあえず周期割り込みだけでも実装する
 */
#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#include <stdint.h>

/**
 * 周期的割り込みリスナ
 */
typedef struct {
	/**
	 * 割り込みハンドラ．
	 * 割り込み時に実行したい関数ポインタを登録すること．
	 * 戻り値で次の割り込みまでのカウント数を指定する．
	 * @return 次の割り込みまでのカウント数
	 */
	uint16_t (*onInterrupt)(void);
} PeriodicInterruptListener;

/**
 * 周期的割り込みコントローラ．
 * カウント単位で割り込み周期を設定できる．
 * setPeriodCountで割り込み時のカウントを設定して使うこと．
 * 初期値はカウンタの最大値(8ビットなら255，16ビットなら65535)
 * オーバーフローで1カウントなので，実際の周期は+1カウント．
 * 実際に利用するにはaddInterruptListenerで割り込みリスナを登録し，
 * enableInterruptで割り込みを有効にする必要がある．
 */
typedef struct {
	/**
	 * 割り込み時のカウントを設定する
	 * @param 割り込み時のカウント，タイマのカウンタサイズによって最大値が異なることに注意
	 */
	void (*setPeriodCount)(uint16_t);
	/**
	 * 割り込みリスナを登録する
	 * @param 割り込みリスナ
	 */
	void (*addInterruptListener)(PeriodicInterruptListener*);
	/**
	 * 割り込みを有効にする
	 * @param 優先度を表す列挙型，Hardware.hで定義
	 */
	void (*enableInterrupt)(int priority);
	/**
	 * 割り込みを無効にする
	 */
	void (*disableInterrupt)(void);
} PeriodicInterruptController;

/**
 * タイマモジュール
 */
typedef struct {
	/**
	 * タイマのカウントを有効にする．
	 */
	void (*start)(void);
	/**
	 * タイマを一時停止する．
	 */
	void (*stop)(void);
	/**
	 * タイマのカウントを取得する．
	 * @return タイマの現在のカウント
	 */
	uint16_t (*getCount)(void);
	/**
	 * タイマのカウントを設定する．
	 * @param 設定するカウント
	 */
	void (*setCount)(uint16_t);
	/**
	 * 周期的割り込みコントローラを取得する
	 * @return 周期的割り込みのコントローラ
	 */
	PeriodicInterruptController* (*getPeriodicInterruptController)(void);
} TimerModule;

#endif /* TIMER_MODULE_H */
