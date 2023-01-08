//
// Created by Tony on 04/07/2022.
//

#ifndef MYVERSE_ENTITYEXECUTIONSTATE_H
#define MYVERSE_ENTITYEXECUTIONSTATE_H

namespace Client {

	enum EntityExecutionState
	{
		PreAwake,
		Awake,
		OnEnable,
		Start,
		Update,
		OnDisable,
		Destroy,
		PostDestroy
	};

} // Client

#endif // MYVERSE_ENTITYEXECUTIONSTATE_H
