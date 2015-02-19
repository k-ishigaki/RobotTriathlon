/*
 * タイマモジュールのインターフェース定義
 * 8ビットタイマと16ビットタイマでインターフェースが異なるので
 * 分けている
 */
#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

/**
 * TimerModuleの割り込みリスナ
 */
typedef struct {
	/**
	 * 割り込みハンドラ
	 * オーバーフロー割り込みのみをサポート
	 */
	void (*onInterrupt)(void);
} TimerModule_InterruptListener;

typedef struct {
	/**
	 * 割り込みを有効にする
	 */
	void (*enableInterrupt)(void);
	/**
	 * 割り込みを無効にする
	 */
	void (*disableInterrupt)(void);
	/**
	 * 割り込みの優先度を設定する
	 * 優先度に指定できる列挙型定数はHardware.hで定義
	 */
	void (*setInterruptPriority)(int);
	/**
	 * 割り込みリスナを登録する
	 * @param 割り込みリスナ
	 */
	void (*addInterruptListener)(TimerModule_InterruptListener*);
} TimerModule_InterruptController;

typedef struct {
	/**
	 * カウント値を取得する
	 * @return 取得したカウント値
	 */
	uint8_t (*getCount)(void);
	/**
	 * カウント値を設定する
	 * @param 設定するカウント値
	 */
	void (*setCount)(uint8_t);
	/**
	 * プレスケーラ値を設定する
	 * 対応している値はデータシートを参照すること
	 * @param プレスケーラ値，無効な値の時は何もしない
	 */
	void (*setPrescalerValue)(uint8_t);
	/**
	 * ポストスケーラ値を設定する
	 * 対応している値はデータシートを参照すること
	 * @param ポストスケーラ値，無効な値の時は何もしない
	 */
	void (*setPostscalerValue)(uint16_t);
	/**
	 * 割り込み時カウンタ値を設定する
	 * @param 割り込み時カウンタ値
	 */
	void (*setPeriodCount)(uint8_t);
} TimerModule_8bitTimer;

typedef struct {
	/**
	 * カウント値を取得する
	 * @return 取得したカウント値
	 */
	uint16_t (*getCount)(void);
	/**
	 * カウント値を設定する
	 * @param 設定するカウント値
	 */
	void (*setCount)(uint16_t);
	/**
	 * プレスケーラ値を設定する
	 * 対応している値はデータシートを参照すること
	 * @param プレスケーラ値，無効な値の時は何もしない
	 */
	void (*setPrescalerValue)(uint8_t);
} TimerModule_16bitTimer;

/**
 * TimerModuleのインターフェース
 */
typedef struct {
	/**
	 * タイマを有効にする
	 */
	void (*enable)(void);
	/**
	 * タイマを無効にする
	 */
	void (*disable)(void);
	/**
	 * タイマのクロックソースを指定する
	 * 引数にはHardware.hの列挙型定数を入れること
	 * @param クロックソースを示す列挙型定数
	 */
	void (*selectClockSource)(int);
	/**
	 * 割り込みコントローラを取得する
	 * @return TimerModule_InterruptControllerのインスタンス
	 */
	TimerModule_InterruptController* (*getInterruptController)(void);
	/**
	 * 8ビットタイマを取得する
	 * @return TimerModule_8bitTimerのインスタンス
	 */
	TimerModule_8bitTimer* (*get8bitTimer)(void);
	/**
	 * 16ビットタイマを取得する
	 * @return TimerModule_16bitTimerのインスタンス
	 */
	TimerModule_16bitTimer* (*get16bitTimer)(void);
} TimerModule;

#endif /* TIMER_MODULE_H */
