Stock Trading Strategies Creator
================================

Stock Trading Strategies Creator (STSC) is a bunch of utilities on C++ that could be used to create market trading strategies.

 * common. Module 'common' include all common classes-types-structures and processing prototypes-mechanisms.

*bar_types.h, bar_types.cpp* have
  struct bar_type;

*signal_types.h, signal_types.cpp* have
  signal_type - open, close
  class signal - signal prototype (abstract class)
  struct close_signal : public signal
  struct open_signal : public signal - long, short


 * algorithm_storage. Module 'algorithm_storage' include algorithm_prototype, strategies engine, signal_vector.

*signal_vector.h, signal_vector.cpp* store signal_vector template class, this class store signals that algorithms will produce.
  Please read Attention note and see tests - to understand how to use this vector out of library

*strategies_engine.h, strategies_engine.cpp* strategies_engine class created to store and control algorithms.
  TODO: this class should correctly run algorithms mechanisms to produce signals
  
*algorithms/ algorithm_prototype.h, algorithm_prototype.cpp* algorithm_prototype template - is a prototype for all algorithms
  see tests to see correct using examples with creating subscriptions to other algorithms data
