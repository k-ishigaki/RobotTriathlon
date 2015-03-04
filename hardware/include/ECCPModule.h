#ifndef ECCP_MODULE_H
#define ECCP_MODULE_H

#include <stdint.h>

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
	 * PWMのデューティー比を設定する．
	 * @param デューティー比，設定可能な値の範囲はタイマ依存
	 */
	void (*setPWMDutyCount)(uint16_t);
} PWMDriver;

typedef struct {
	/**
	 * PWMのデューティー比を設定する．
	 * @param デューティー比，設定可能な値の範囲はタイマ依存
	 */
	void (*setPWMDutyCount)(uint16_t);
	/**
	 * PWMの出力モードを変更する．
	 * @param モードを表す識別子，Hardware.hで定義
	 * @param 出力モードを表す識別子，Hardware.hで定義
	 */
	void (*setPWMOutputMode)(int, int);
} EnhancedPWMDriver;

typedef struct {
	/**
	 * コンペアマッチのインターフェースを返す．
	 * @return コンペアマッチのインターフェース
	 */
	CompareMatchInterruptController* (*getCompareMatchInterruptController)(void);
	/**
	 * 標準PWMドライバのインターフェースを返す．
	 * @return PWMドライバのインターフェース
	 */
	PWMDriver* (*getPWMDriver)(void);
	/**
	 * 拡張PWMドライバのインターフェースを返す．
	 * @return 拡張PWMドライバのインターフェース
	 */
	EnhancedPWMDriver* (*getEnhancedPWMDriver)(void);
} ECCPModule;

#endif /* ECCP_MODULE_H */
