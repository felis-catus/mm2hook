#pragma once
#include "mm2_common.h"

namespace MM2
{
    // Forward declarations
    extern class Base;
    extern class asCullable;
    extern class asNode;

    // External declarations
    extern class datParser;

    class Base {
    protected:
        static AGEHook<0x4C8200>::MemberFunc<void> $$dtor;
    public:
        AGE_API virtual ~Base() {
            PUSH_VTABLE();
            $$dtor(this);
            POP_VTABLE();
        };
    };

    class asCullable : public Base {
    protected:
        static AGEHook<0x460EA0>::MemberFunc<void> $$dtor;
        static AGEHook<0x4A3440>::MemberFunc<void> $Cull;
    public:
        AGE_API virtual ~asCullable() {
            PUSH_VTABLE();
            $$dtor(this);
            POP_VTABLE();
        };

        AGE_API virtual void Cull(void) {
            $Cull(this);
        };
    };

    class asNode : public asCullable {
        asNode *next;
        asNode *child; // not sure on this one
        asNode *parent;

        unsigned int flags; // not sure how these work yet

        LPCSTR name;
    protected:
        static AGEHook<0x403330>::MemberFunc<void> $FileIO;
        static AGEHook<0x403340>::MemberFunc<void> $AfterLoad;
        static AGEHook<0x403350>::MemberFunc<void> $BeforeSave;

        static AGEHook<0x403360>::MemberFunc<char *> $GetClassNameA;

        static AGEHook<0x4A0CE0>::MemberFunc<void> $$ctor;
        static AGEHook<0x4A0D00>::MemberFunc<void> $$dtor;

        static AGEHook<0x4A0D70>::MemberFunc<void> $SetName;

        static AGEHook<0x4A0DA0>::MemberFunc<const char *> $GetDirName;

        static AGEHook<0x4A0DB0>::MemberFunc<void> $Update;
        static AGEHook<0x4A0DD0>::MemberFunc<void> $UpdatePaused;
        static AGEHook<0x4A0E10>::MemberFunc<void> $Reset;
        static AGEHook<0x4A0E30>::MemberFunc<void> $ResChange;

        static AGEHook<0x4A0E60>::MemberFunc<int> $AddChild;
        static AGEHook<0x4A0EE0>::MemberFunc<int> $InsertChild;
        static AGEHook<0x4A0F50>::MemberFunc<int> $RemoveChild_$1;
        static AGEHook<0x4A0FD0>::MemberFunc<int> $RemoveChild_$2;
        static AGEHook<0x4A1010>::MemberFunc<void> $RemoveAllChildren;
        static AGEHook<0x4A1030>::MemberFunc<asNode *> $GetChild;
        static AGEHook<0x4A1060>::MemberFunc<asNode *> $GetNext;
        static AGEHook<0x4A1070>::MemberFunc<asNode *> $GetLastChild;
        static AGEHook<0x4A10A0>::MemberFunc<int> $NumChildren;
        static AGEHook<0x4A10C0>::MemberFunc<void> $SwitchTo;

        static AGEHook<0x4A1120>::MemberFunc<bool> $Load;
        static AGEHook<0x4A11D0>::MemberFunc<bool> $Save;
    public:
        AGE_API asNode() {
            PUSH_VTABLE();
            $$ctor(this);
            POP_VTABLE();
        };

        AGE_API virtual ~asNode() {
            PUSH_VTABLE();
            $$dtor(this);
            POP_VTABLE();
        };

        AGE_API void SetName(LPCSTR name) {
            $SetName(this, name);
        };

        AGE_API int AddChild(asNode *child) {
            return $AddChild(this, child);
        };

        AGE_API int InsertChild(int index, asNode *child) {
            return $InsertChild(this, index, child);
        };

        AGE_API int RemoveChild(int index) {
            return $RemoveChild_$1(this, index);
        };

        AGE_API int RemoveChild(asNode *child) {
            return $RemoveChild_$2(this, child);
        };

        AGE_API void RemoveAllChildren(void) {
            $RemoveAllChildren(this);
        };

        AGE_API asNode * GetChild(int index) {
            return $GetChild(this, index);
        };

        AGE_API asNode* GetNext(void) {
            return $GetNext(this);
        };

        AGE_API asNode* GetLastChild(void) {
            return $GetLastChild(this);
        };

        AGE_API int NumChildren(void) {
            return $NumChildren(this);
        };

        AGE_API void SwitchTo(int index) {
            $SwitchTo(this, index);
        };

        /*
            *** DO NOT CHANGE THE ORDER OF THESE ***
            They must EXACTLY match the virtual tables in MM2!
        */

        AGE_API virtual void Update(void) {
            $Update(this);
        };

        AGE_API virtual void Reset(void) {
            $Reset(this);
        };

        AGE_API virtual void ResChange(int width, int height) {
            $ResChange(this, width, height);
        };

        AGE_API virtual void UpdatePaused(void) {
            $UpdatePaused(this);
        };

        AGE_API virtual void FileIO(datParser &parser) {
            $FileIO(this, &parser);
        };

        AGE_API virtual void AfterLoad(void) {
            $AfterLoad(this);
        };

        AGE_API virtual void BeforeSave(void) {
            $BeforeSave(this);
        };

        AGE_API virtual bool Save(void) {
            return $Save(this);
        };

        AGE_API virtual bool Load(void) {
            return $Load(this);
        };

        AGE_API virtual char * GetClassName(void) {
            return $GetClassNameA(this);
        };

        AGE_API virtual const char * GetDirName(void) {
            return $GetDirName(this);
        };
    };
}