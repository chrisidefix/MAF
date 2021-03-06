/*
 *  mafImporterVTK.cpp
 *  mafPluginVTK
 *
 *  Created by Paolo Quadrani on 04/04/11.
 *  Copyright 2011 SCS-B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include "mafImporterVTK.h"
#include <mafVME.h>
#include <mafDataSet.h>

#include <vtkDataSetReader.h>

using namespace mafPluginVTK;
using namespace mafResources;

mafImporterVTK::mafImporterVTK(const QString code_location) : mafImporter(code_location) {
    m_Reader = vtkDataSetReader::New();
    setProperty("wildcard", mafTr("VTK Files (*.vtk)"));
}

mafImporterVTK::~mafImporterVTK() {
    m_Reader->Delete();
}

void mafImporterVTK::execute() {
    QMutex mutex(QMutex::Recursive);
    QMutexLocker locker(&mutex);

    m_Status = mafOperationStatusExecuting;
    
    checkImportFile();
    if (m_Status == mafOperationStatusAborted) {
        cleanup();
        return;
    }
    
    QByteArray ba = filename().toAscii();
    m_Reader->SetFileName(ba.constData());
    m_Reader->Update();
    
    m_ImportedData = m_Reader->GetOutputPort();
    m_ImportedData.setExternalCodecType("VTK");
    m_ImportedData.setClassTypeNameFunction(vtkClassTypeNameExtract);
    QString dataType = m_ImportedData.externalDataType();

    //here set the mafDataset with the VTK data
    importedData(&m_ImportedData);
    
    //set the default boundary algorithm for VTK vme
    mafResources::mafVME * vme = qobject_cast<mafResources::mafVME *> (this->m_Output);
    vme->dataSetCollection()->itemAtCurrentTime()->setBoundaryAlgorithmName("mafPluginVTK::mafDataBoundaryAlgorithmVTK");

    if (dataType.compare("vtkPolyData") == 0) {
        vme->setProperty("iconType", "mafVMESurfaceVTK");
    } else {
        vme->setProperty("iconType", "mafVMEVolumeVTK");
    }
    
    Q_EMIT executionEnded();
}
