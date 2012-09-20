/**

Game Develop - Video Object Extension
Copyright (c) 2010-2012 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#ifndef VIDEOOBJECT_H
#define VIDEOOBJECT_H

#include "GDL/Object.h"
#include "VideoWrapper.h"
class ImageManager;
class RuntimeScene;
class Object;
class ObjectsConcerned;
class ImageManager;
class InitialPosition;
#if defined(GD_IDE_ONLY)
class wxBitmap;
class Game;
class wxWindow;
namespace gd { class MainFrameWrapper; }
namespace gd {class ResourcesMergingHelper;}
#endif

/**
 * Video Object
 */
class GD_EXTENSION_API VideoObject : public Object
{
public :

    VideoObject(std::string name_);
    virtual ~VideoObject();
    virtual Object * Clone() const { return new VideoObject(*this);}

    virtual bool LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr );
    virtual bool LoadRuntimeResources(const RuntimeScene & scene, const ImageManager & imageMgr );
    virtual bool InitializeFromInitialPosition(const InitialPosition & position);

    virtual bool Draw(sf::RenderTarget & renderTarget);

    #if defined(GD_IDE_ONLY)
    virtual bool DrawEdittime(sf::RenderTarget & renderTarget);
    virtual void ExposeResources(gd::ArbitraryResourceWorker & worker);
    virtual bool GenerateThumbnail(const gd::Project & project, wxBitmap & thumbnail);

    virtual void EditObject( wxWindow* parent, Game & game_, gd::MainFrameWrapper & mainFrameWrapper_ );
    virtual wxPanel * CreateInitialPositionPanel( wxWindow* parent, const Game & game_, const Scene & scene_, const InitialPosition & position );
    virtual void UpdateInitialPositionFromPanel(wxPanel * panel, InitialPosition & position);

    virtual void GetPropertyForDebugger (unsigned int propertyNb, std::string & name, std::string & value) const;
    virtual bool ChangeProperty(unsigned int propertyNb, std::string newValue);
    virtual unsigned int GetNumberOfProperties() const;
    #endif

    virtual void LoadFromXml(const TiXmlElement * elemScene);
    #if defined(GD_IDE_ONLY)
    virtual void SaveToXml(TiXmlElement * elemScene);
    #endif

    virtual void UpdateTime(float timeElapsed);

    virtual void OnPositionChanged();

    /**
     * Change the video file loaded when a call is made to LoadRuntimeResources
     */
    void SetVideoFile(std::string file) { videoFile = file; }

    /**
     * Get video filename.
     */
    std::string GetVideoFile() const { return videoFile; }

    /**
     * Load and start video using the video Filename.
     */
    void ReloadVideo();

    /**
     * Set the looping of the video
     */
    void SetLooping(bool loop_) { looping = loop_; video.SetLooping(looping); }

    /**
     * Return true if looping is activated
     */
    bool GetLooping() const { return looping; }

    bool IsPaused() const { return paused; };

    unsigned int GetVolume();
    void SetVolume(unsigned int vol);

    virtual float GetWidth() const;
    virtual float GetHeight() const;
    virtual void SetWidth(float ) {};
    virtual void SetHeight(float ) {};

    virtual float GetDrawableX() const;
    virtual float GetDrawableY() const;

    virtual float GetCenterX() const;
    virtual float GetCenterY() const;

    virtual bool SetAngle(float newAngle);
    virtual float GetAngle() const {return angle;};

    void SetOpacity(float val);
    inline float GetOpacity() const {return opacity;};

    void SetColor(unsigned int r,unsigned int v,unsigned int b);
    inline unsigned int GetColorR() const { return colorR; };
    inline unsigned int GetColorG() const { return colorG; };
    inline unsigned int GetColorB() const { return colorB; };

    /**
     * Only used internally by GD events generated code: Prefer using original SetColor.
     */
    void SetColor(const std::string & colorStr);

    virtual std::vector<Polygon2d> GetHitBoxes() const;

    void LoadAndPlayVideo( const std::string & videoFile );

    void Seek( double position );

    double GetTimePosition() const;
    double GetDuration() const;

private:

    std::string videoFile;
    VideoWrapper video;

    bool looping;
    bool paused;

    //Opacity
    float opacity;

    //Color
    unsigned int colorR;
    unsigned int colorG;
    unsigned int colorB;

    float angle;
};

void DestroyVideoObject(Object * object);
Object * CreateVideoObject(std::string name);

#endif // VIDEOOBJECT_H

