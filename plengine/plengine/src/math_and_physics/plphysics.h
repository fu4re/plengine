#pragma once
#ifndef __PLPHYSICS_H__
#define __PLPHYSICS_H__

#ifdef WIN32
#define stdcall __stdcall
#else
#define stdcall
#endif
typedef void stdcall update();

#include "physics.h"
int max_parts_in_destroy;

void InitializePhysics(Space *);
#define ChangeSpace InitializePhysics

void PutObject(int, Object *);

Space * GetSpace();

void UpdatePhysics();

void Loop(bool /*condition*/, Time /*sleep*/, update /*Update*/);
#endif
