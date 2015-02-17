/*
 * タイマモジュールのインターフェース定義
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
} TimerModuleInterruptListener;

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
	 * タイマをリセットする
	 */
	void (*reset)(void);
	/**
	 * 割り込みリスナを登録する
	 * @param 割り込みリスナ
	 */
	void (*addInterruptListener)(TimerModuleInterruptListener*);
	/**
	 * 割り込みを有効にする
	 */
	void (*enableInterrupt)(void);
	/**
	 * 割り込みを無効にする
	 */
	void (*disableInterrupt)(void);
	// --------- これ以降は各モジュール依存 ----------
	/**
	 * タイマのクロックソースを指定する
	 * 引数にはHardware.hの列挙型定数を入れること
	 * @param クロックソースを示す列挙型定数
	 */
	void (*selectClockSource)(int);
	/**
	 * プリスケーラ値を設定する
	 * 対応しているプリスケーラ値はデータシートまたはソースコードで確認すること
	 * @param プリスケーラ値
	 */
	void (*setPrescalerValue)(uint16_t);
	/**
	 * ポストスケーラ値を設定する
	 * 対応しているポストスケーラ値はデータシートまたはソースコードで確認すること
	 * @param ポストスケーラ値
	 */
	void (*setPostscalerValue)(uint16_t);
	/**
	 * カウント値を設定する
	 * 8ビットと16ビットで設定できる値の範囲が異なることに注意
	 * @param カウント値
	 */
	void (*setCount)(uint16_t);
	/**
	 * カウント値を取得する
	 * @return カウント値
	 */
	uint16_t (*getCount)(void);
	/**
	 * 割り込み時カウンタ値を設定する
	 * @param 割り込み時カウンタ値
	 */
	void (*setPeriodCount)(uint16_t);
} TimerModule;

#endif /* TIMER_MODULE_H */
