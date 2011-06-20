/*
 *  mafPipeVisualVTK.h
 *  mafPluginVTK
 *
 *  Created by Daniele Giunchi - Paolo Quadrani on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFVISUALPIPEVTK_H
#define MAFVISUALPIPEVTK_H

// Includes list
#include "mafPluginVTKDefinitions.h"
#include <mafPipeVisual.h>

// Foundation Class forwarding list
class vtkRenderer;
class vtkProp3D;

namespace mafPluginVTK {

/**
 Class name: mafPipeVisualVTK
 This class represents visual pipe used to render VTK polydata.
 */

class MAFPLUGINVTKSHARED_EXPORT mafPipeVisualVTK : public mafResources::mafPipeVisual {
    Q_OBJECT
    Q_PROPERTY(bool scalarVisibility READ scalarVisibility WRITE setScalarVisibility)
    Q_PROPERTY(bool immediateRendering READ immediateRendering WRITE setImmediateRendering)
    /// typedef macro.
    mafSuperclassMacro(mafResources::mafPipeVisual);

public:
    /// Object constructor;
    mafPipeVisualVTK(const QString code_location = "");
    
    /// Return the flag to activate scalar visibility.
    bool scalarVisibility();

    /// Set the flag to activate scalar visibility.
    void setEdgeVisibility(bool edgeVisibility);

    /// Return the flag to activate edge visibility.
    int edgeVisibility();

    /// Return the flag to activate immediate rendering mode.
    bool immediateRendering();

public slots:

    /// Set the flag to activate scalar visibility.
    void setScalarVisibility(bool scalarVisibility);

    /// Set the flag to activate immediate rendering mode.
    void setImmediateRendering(bool immediateRendering);

protected:
    /// Object destructor.
    /* virtual */ ~mafPipeVisualVTK();
    
    /// Update the pipeline with the new graphic object.
    /*virtual*/ void updatedGraphicObject();
    
    /// update visibility for actor or volume passed as parameter
    void updateVisibility(vtkProp3D *prop);

private:
    vtkRenderer * m_Renderer; ///< Current VTK Renderer.
    bool m_ScalarVisibility; ///< Flag to activate scalar visibility.
    bool m_ImmediateRendering; ///< Flag to activate immediate rendering mode.
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

inline bool mafPipeVisualVTK::scalarVisibility() {
    return m_ScalarVisibility;
}

inline bool mafPipeVisualVTK::immediateRendering() {
    return m_ImmediateRendering;
}

} // namespace mafPluginVTK

#endif // MAFVISUALPIPEVTK_H
