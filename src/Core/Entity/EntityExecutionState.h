//
// Created by Tony on 04/07/2022.
//

#ifndef MYVERSE_ENTITYEXECUTIONSTATE_H
#define MYVERSE_ENTITYEXECUTIONSTATE_H

namespace Core {

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

} // Core

#endif // MYVERSE_ENTITYEXECUTIONSTATE_H
