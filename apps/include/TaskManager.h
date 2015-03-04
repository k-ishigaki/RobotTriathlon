#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Hardware.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	/**
	 * タスク割り込みから呼ばれる．
	 * 割り込み中なので短い時間で処理を行わなければならない．
	 * 戻り値をfalseにすると，次からはこのタスクの次に登録されているタスクが呼ばれる．
	 * @return true：次の割り込みもこのタスクが呼ばれる，false：次のタスクへ引き渡す．
	 */
	bool (*onTaskCalled)(void);
} PeriodicCalledTask;

typedef struct {
	/**
	 * タスクを追加する．
	 * タスクの追加順に注意すること．
	 * @param 周期的に呼ばれることが想定されたタスク
	 */
	void (*addPeriodicCalledTack)(PeriodicCalledTask*);
	/**
	 * タスク呼び出し割り込みを有効にする．
	 */
	void (*enableTaskInterrupt)(void);
	/**
	 * タスク呼び出し割り込みを無効にする．
	 */
	void (*disableTaskInterrupt)(void);
} TaskManager;

/**
 * タスクマネージャのインターフェースを取得する．
 * 割り込みソースには周期的割り込みリスナを使う．
 */
TaskManager* getTaskManger1(PeriodicInterruptController*);
TaskManager* getTaskManger2(PeriodicInterruptController*);

#endif /* TASK_MANAGER_H */
