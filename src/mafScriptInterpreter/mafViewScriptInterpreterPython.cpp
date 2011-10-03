/*
 *  mafViewScriptInterpreterPython.h
 *  mafScriptInterpreter
 *
 *  Created by Paolo Quadrani on 03/10/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include "mafViewScriptInterpreterPython.h"
#include "mafInterpreterConsole.h"
#include "mafScriptEditorPython.h"
#include "mafScriptEditorPool.h"

using namespace mafScriptInterpreter;

mafViewScriptInterpreterPython::mafViewScriptInterpreterPython(const QString code_location) : mafViewScriptInterpreter(code_location) {
}

mafViewScriptInterpreterPython::~mafViewScriptInterpreterPython() {
}

void mafViewScriptInterpreterPython::create() {
    mafScriptEditor *interpreter = mafScriptEditorPool::instance()->python();

    ((mafInterpreterConsole*)m_RenderWidget)->registerInterpreter(interpreter);
}