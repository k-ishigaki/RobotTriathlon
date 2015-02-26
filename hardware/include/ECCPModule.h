#ifndef ECCP_MODULE_H
#define ECCP_MODULE_H

typedef struct {
	/**
	 * コンペアマッチ割り込みが発生した時に呼び出される．
	 * @return コンペアマッチの値，変更しない場合は0を返すこと
	 */
	uint16_t (*onCompareMatched)(void);
} CompareMatchInterruptListener;

typedef struct {
	/**
	 * コンペアマッチが発生するときの値を設定する．
	 * @param タイマの値と比較される値
	 */
	void (*setCompareMatchCount)(uint16_t);
	/**
	 * コンペアマッチ時に呼び出されるリスナの登録．
	 * @param コンペアマッチ割り込みリスナ
	 */
	void (*addCompareMatchInterruptListener)(CompareMatchInterruptListener*);
	/**
	 * コンペアマッチ割り込みを有効にする．
	 * @param 割り込み優先度，Hardware.hで定義される列挙型定数
	 */
	void (*enableCompareMatchInterrupt)(int);
	/**
	 * コンペアマッチ割り込みを無効にする．
	 */
	void (*disableCompareMatchInterrupt)(void);
} CompareMatchInterruptController;

typedef struct {
	/**
	 * コンペアマッチのインターフェースを返す．
	 * @return コンペアマッチのインターフェース
	 */
	CompareMatchInterruptController* (*getCompareMatchInterruptController)(void);
} ECCPModule;

#endif /* ECCP_MODULE_H */
