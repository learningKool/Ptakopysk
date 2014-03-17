#ifndef __PTAKOPYSK__TWEEN__
#define __PTAKOPYSK__TWEEN__

#include <XeCore/Common/Base.h>
#include <XeCore/Common/IRtti.h>
#include <XeCore/Common/MemoryManager.h>
#include <XeCore/Common/Singleton.h>
#include <XeCore/Common/Property.h>
#include "Math.h"
#include <list>

namespace Ptakopysk
{

    class ITween
    {
        friend class Tweener;
    public:
        ITween() {};
        virtual ~ITween() {};

        virtual int getState() = 0;

    protected:
        virtual void onStart() = 0;
        virtual void onStop() = 0;
        virtual void onUpdate( float dt ) = 0;
        virtual dword getPropertyID() = 0;
    };

    template< typename PT, typename OT, PT(*EF)(float,PT,PT,float) >
    class Tween
    : public ITween
    {
    public:
        FORCEINLINE Tween( XeCore::Common::Property< PT, OT >& property, PT to, float duration, float startTime = 0.0f );
        FORCEINLINE virtual ~Tween() {};

        FORCEINLINE virtual int getState() { return m_state; };

    protected:
        FORCEINLINE virtual void onStart();
        FORCEINLINE virtual void onStop();
        FORCEINLINE virtual void onUpdate( float dt );
        FORCEINLINE virtual dword getPropertyID();

    private:
        XeCore::Common::Property< PT, OT >& m_property;
        PT m_from;
        PT m_to;
        float m_duration;
        float m_time;
        int m_state; // -1: not started; 0: in progress; 1: complete.
    };

    class Tweener
    : public virtual XeCore::Common::IRtti
    , public virtual XeCore::Common::MemoryManager::Manageable
    , public XeCore::Common::Singleton< Tweener >
    {
        RTTI_CLASS_DECLARE( Tweener );

    public:
        Tweener();
        virtual ~Tweener();

        bool hasTween( dword id );
        dword startTween( const ITween* t );
        void killTween( dword id );
        template< typename PT, typename OT >
        void killTweensOf( const XeCore::Common::Property< PT, OT >& p );
        void killAllTweens();

        void processTweens( float dt );

    private:
        std::list< ITween* > m_tweens;
    };

}

#include "Tween.inl"

#endif
