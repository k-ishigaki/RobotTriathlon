/*
 * PICのOscillatorモジュールを操作するオブジェクト
 * モードとクロックの選択のみを行える
 * 他の機能は未実装
 * 内部クロックでPLLを有効にする場合はここでは内部クロックの出力を
 * 決めることしかできないため，データシートで確認すること
 */

#ifndef OSCILLATOR_MODULE_H
#define OSCILLATOR_MODULE_H

typedef void (*OscillatorModule_setMode)(int mode);
typedef void (*InternalOscillator_selectFrequency)(int frequency);

typedef struct {
	/**
	 * 内部オシレータの周波数を選択する
	 * @param 周波数を示す列挙子(Hardware.hで定義)
	 */
	InternalOscillator_selectFrequency selectFrequency;
} InternalOscillator;

typedef struct {
	/**
	 * モードを選択する
	 * @param モードを示す列挙子(Hardware.hで定義)
	 */
	OscillatorModule_setMode setMode;
	/**
	 * 内部オシレータのオブジェクトを取得する
	 * @return 内部オシレータのオブジェクト
	 */
	InternalOscillator* (*getInternalOscillator)(void);
} OscillatorModule;

#endif /* OSCILLATOR_MODULE_H */
