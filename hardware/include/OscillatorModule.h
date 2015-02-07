/*
 * PICのOscillatorモジュールを操作するオブジェクト
 * モードとクロックの選択のみを行える
 * 他の機能は未実装
 * 内部クロックでPLLを有効にする場合はここでは内部クロックの出力を
 * 決めることしかできないため，データシートで確認すること
 */

#ifndef OSCILLATOR_MODULE_H
#define OSCILLATOR_MODULE_H

typedef struct {
	/**
	 * 内部オシレータの周波数を設定する
	 * 無効な値を指定した時は何もしない
	 * @param 周波数(Hz)，いくつかの値に限られる
	 */
	void (*setFrequency)(unsigned long frequency);
} InternalOscillator;

typedef struct {
	/**
	 * PLLを有効にする
	 */
	void (*enablePLL)(void);
	/**
	 * PLLを無効にする
	 */
	void (*disablePLL)(void);
} PhaseLockedLoop;

typedef struct {
	/**
	 * モードを選択する
	 * @param モードを示す列挙子(Hardware.hで定義)
	 */
	void (*selectSystemClock)(int mode);
	/**
	 * 内部オシレータのオブジェクトを取得する
	 * @return 内部オシレータのオブジェクト
	 */
	InternalOscillator* (*getInternalOscillator)(void);
	/**
	 * PLLを設定するオブジェクトを取得する
	 * @return PLLの設定をするオブジェクト，持っていない場合はNULL
	 */
	PhaseLockedLoop* (*getPhaseLockedLoop)(void);
} OscillatorModule;

#endif /* OSCILLATOR_MODULE_H */
