#pragma once

template <typename T>
class TypedAnyView;

class Any {
public:
    Any() {}
    Any(Any const& _other) = delete;
    Any(Any&& _other) = delete;

    virtual ~Any() {}

    auto operator=(Any const& _other) -> Any& = delete;
    auto operator=(Any&& _other) -> Any& = delete;

    template <typename T>
    auto as() -> TypedAnyView<T>* {
        return dynamic_cast<TypedAnyView<T>*>(this);
    }

    template <typename T>
    auto as() const -> TypedAnyView<T> const* {
        return dynamic_cast<TypedAnyView<T> const*>(this);
    }
};

template <typename T>
class TypedAnyView : virtual public Any {
    T& refValue;
public:
    TypedAnyView(T& _refValue) : refValue(_refValue) {}

    auto get() -> T* {
        return &refValue;
    }

    auto get() const -> T* {
        return &refValue;
    }

    auto operator->() -> T* {
        return &refValue;
    }

    auto operator->() const -> T const* {
        return &refValue;
    }
};

template <typename Top, typename ...Ts>
class TypedAny : public TypedAnyView<Top>, public TypedAnyView<Ts>..., virtual public Any {
    Top value;

public:
    TypedAny()
        : TypedAnyView<Top>(value)
        , TypedAnyView<Ts>(value)...
    {}

    using TypedAnyView<Top>::get;
};

