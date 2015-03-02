#ifndef COMPARATOR_MODULE_H
#define COMPARATOR_MODULE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	/**
	 * コンパレータの変化割り込みリスナ
	 * @param 変化したコンパレータの出力，HIGHならtrue，LOWならfalse
	 */
	void (*onComparatorOutputChanged)(bool);
} ComparatorChangeListener;

typedef struct {
	/**
	 * コンパレータのチャンネルを選択する．
	 * @param コンパレータのチャンネル，Hardware.hで定義された列挙型定数
	 */
	void (*selectComparatorChannel)(int);
	/**
	 * コンパレータの値を取得する．
	 * @return コンパレータの出力，LOWならfalse，HIGHならtrue
	 */
	bool (*getComparatorOutput)(void);
	/**
	 * コンパレータ変化割り込みを追加する．
	 * @param コンパレータの変化割り込みリスナ
	 */
	void (*addComparatorChangeListener)(ComparatorChangeListener*);
	/**
	 * コンパレータ変化割り込みを有効にする．
	 * @param 割り込み優先度，Hardware.hに定義された列挙型定数
	 */
	void (*enableComparatorChangeInterrupt)(int);
	/**
	 * コンパレータ変化割り込みを無効にする．
	 */
	void (*disableComparatorChangeInterrupt)(void);
} ComparatorModule;

#endif /* COMPARATOR_MODULE_H */
