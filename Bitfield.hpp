#pragma once

namespace Bitfields {
  template<unsigned startBit, unsigned numBits, typename Container = std::uint32_t>
  struct Bitfield {
  private:
    constexpr static auto mask() {
      Container out{};
      for(unsigned i = startBit; i < startBit + numBits; ++ i) {
        out |= Container{1} << i;
      }
      return out;
    }
  public:
    
    static auto constexpr selfMask = mask();
    static auto constexpr otherMask = ~selfMask;

    static_assert(startBit + numBits <= sizeof(Container) * 8);

    constexpr operator Container() const {
      return (*reinterpret_cast<Container const *>(this) & selfMask) >> startBit;
    }

    constexpr auto operator=(Container val) {
      return *reinterpret_cast<Container*>(this) =
            (*reinterpret_cast<Container*>(this) & otherMask) | ((val << startBit) & selfMask);
    }

    constexpr Bitfield &operator+= (Container val) { return *this = *this + val; }
    constexpr Bitfield &operator-= (Container val) { return *this = *this - val; }
    constexpr Bitfield &operator*= (Container val) { return *this = *this * val; }
    constexpr Bitfield &operator/= (Container val) { return *this = *this / val; }
    constexpr Bitfield &operator%= (Container val) { return *this = *this % val; }
    constexpr Bitfield &operator^= (Container val) { return *this = *this ^ val; }
    constexpr Bitfield &operator&= (Container val) { return *this = *this & val; }
    constexpr Bitfield &operator|= (Container val) { return *this = *this | val; }
    constexpr Bitfield &operator>>=(Container val) { return *this = *this >> val; }
    constexpr Bitfield &operator<<=(Container val) { return *this = *this << val; }
    constexpr Bitfield &operator++ ()              { return *this = *this + 1; }
    constexpr Container operator++ (int)           { Conatiner save = *this; ++(*this); return save; }
    constexpr Bitfield &operator-- ()              { return *this = *this - 1; }
    constexpr Container operator-- (int)           { Container save = *this; --(*this); return save; }
  };
}
