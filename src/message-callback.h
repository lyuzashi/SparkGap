#ifndef MESSAGE_CALLBACK_H
#define MESSAGE_CALLBACK_H

enum SlotType { Function, Method };

// The Slot base class, its template parameter indicates the datatype of the parameters it expects to receive. Slots can only
// be connected to Signals with identical ParameterTypes.
template <class ParameterTypeA, class ParameterTypeB, class ParameterTypeC> class Slot {
protected:
    SlotType _slotType;

    Slot(SlotType slotType) : _slotType(slotType) { }

public:
    virtual ~Slot() { }

    // Allows the slot to be called by the signal during firing.
    virtual void operator()(ParameterTypeA paramA, ParameterTypeB paramB, ParameterTypeC paramC) const = 0;

    // Allows the slot to be removed via comparison.
    virtual bool operator==(const Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>* slot) const = 0;

    // Allows the signal to take a copy of the slot so that it can maintain an internal reference to it upon connection.
    // Essentially a virtual copy consructor.
    virtual Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>* clone() const = 0;
    
    // Provides roughly the same mechanism as RTTI.
    SlotType slotType() const {
        return _slotType;
    }
};

// The Signal class, we can implant these into ends and allow means to connect their members to them should they want to
// receive callbacks from their children means. Ofcourse it's possible that these callbacks are made within the context of
// an interrupt so the receipient will want to be fairly quick about how they process it.
template <class ParameterTypeA, class ParameterTypeB, class ParameterTypeC, int Slots = 8> class Signal {
    Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>* _connections[Slots];
	int _nextSlot = 0;

public:
    Signal() { }

    // Since the signal takes copies of all the input slots via clone() it needs to clean up after itself when being destroyed.
    virtual ~Signal() {
        for(int i = 0; i < _nextSlot; ++i)
            delete _connections[i];
    }

    // Adds slot to list of connections.
    void attach(const Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>& slot) {
        if (_nextSlot < (Slots - 1)) {
            // Connect it up and away we go
            _connections[_nextSlot++] = slot.clone();
        }
	}

    // Removes slot from list of connections.
    void detach(const Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>& slot) {
        for (int i = _nextSlot - 1; i >= 0; --i) {
            if (slot == _connections[i]) {
                delete _connections[i];
                --_nextSlot;

                for (int j = i; j < _nextSlot; ++j)
                    _connections[j] = _connections[j + 1];
                _connections[_nextSlot] = NULL;
            }
        }
    }

    // Visits each of its listeners and executes them via operator().
    void fire(ParameterTypeA paramA, ParameterTypeB paramB, ParameterTypeC paramC) const {
        for(int i = 0; i < _nextSlot; ++i)
            (*_connections[i])(paramA, paramB, paramC);
    }
};

// FunctionSlot is a subclass of Slot for use with function pointers. In truth there's not really any need to wrap up free
// standing function pointers into slots since any function in C/C++ is happy to accept a raw function pointer and execute it.
// However this system allows free standing functions to be used alongside member functions or even arbitrary functor objects.
template <class ParameterTypeA, class ParameterTypeB, class ParameterTypeC> class FunctionSlot : public Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC> {
    typedef void (*FunctPtr)(ParameterTypeA, ParameterTypeB, ParameterTypeC);

    // A free standing function pointer.
    FunctPtr _funct;

public:
    FunctionSlot(FunctPtr funct) : Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>(Function), _funct(funct) { }

    // Copy the slot
    Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC> *clone() const {
        return new FunctionSlot<ParameterTypeA, ParameterTypeB, ParameterTypeC>(_funct);
    }

    // Execute the slot.
    void operator() (ParameterTypeA paramA, ParameterTypeB paramB, ParameterType paramC) const {
        return (_funct)(paramA, paramB, paramC);
    }

    // Compares the slot.
    bool operator==(const Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>* slot) const {
        if (slot && slot->slotType() == Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>::_slotType) {
            const FunctionSlot<ParameterTypeA, ParameterTypeB, ParameterTypeC>* functSlot = reinterpret_cast<const FunctionSlot<ParameterTypeA, ParameterTypeB, ParameterTypeC>*>(slot);
            return functSlot && functSlot->_funct == _funct;
        }
        return false;
    }
};

// MethodSlot is a subclass of Slot that allows member function pointers to be used as slots. While free standing
// pointers to functions are relatively intuitive here, Members functions need an additional template parameter, the
// owner object type and they are executed via the ->* operator.
template <class ObjectType, class ParameterTypeA, ParameterTypeB, ParameterTypeC> class MethodSlot : public Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC> {
    typedef void (ObjectType::*FunctPtr)(ParameterTypeA, ParameterTypeB, ParameterTypeC);

    // The function pointer's owner object.
    ObjectType *_obj;

    // A function-pointer-to-method of class ObjectType.
    FunctPtr _funct;

public:
    MethodSlot(ObjectType *obj, FunctPtr funct) : Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>(Method), _obj(obj), _funct(funct) { }

    // Copy the slot.
    Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC> *clone() const {
        return new MethodSlot<ObjectType, ParameterTypeA, ParameterTypeB, ParameterTypeC>(_obj, _funct);
    }

    // Execute the slot.
    void operator() (ParameterTypeA paramA, ParameterTypeB paramB, ParameterTypeC paramC) const {
        return (_obj->*_funct)(paramA, paramB, paramC);
    }

    // Compare the slot.
    bool operator==(const Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>* slot) const {
        if (slot && slot->slotType() == Slot<ParameterTypeA, ParameterTypeB, ParameterTypeC>::_slotType) {
            const MethodSlot<ObjectType, ParameterTypeA, ParameterTypeB, ParameterTypeC>* methSlot = reinterpret_cast<const MethodSlot<ObjectType, ParameterTypeA, ParameterTypeB, ParameterTypeC>*>(slot);
            return methSlot && methSlot->_obj == _obj && methSlot->_funct == _funct;
        }
        return false;
    }
};

#endif // MESSAGE_CALLBACK_H