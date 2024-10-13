#ifndef _H_OPTION
#define _H_OPTION
namespace foundation {
  template<typename T>
  class Option {
    public:
      static Option some(T val);
      static Option none();

      bool is_some();
      bool is_none();
      T unwrap() const;
    private:
      Option(T val);
      Option(bool ok);

      T value;
      bool ok;
  };

template<typename T>
Option<T>::Option(T val)
  : value(val), ok(true) {}

template<typename T>
Option<T>::Option(bool ok)
  : ok(false) {}

template<typename T>
bool Option<T>::is_some() {
  return ok;
}

template<typename T>
bool Option<T>::is_none() {
  return !ok;
}

template<typename T>
T Option<T>::unwrap() const {
  return value;
}

template<typename T>
Option<T> Option<T>::some(T value) {
  return Option<T>(value);
}

template<typename T>
Option<T> Option<T>::none() {
  return Option<T>(false);
}

};
#endif
