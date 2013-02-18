Stock Trading Strategies Creator
================================

Stock Trading Strategies Creator (STSC) is a bunch of utilities on C++ that could be used to create market trading strategies.

 * common. Module 'common' include all common classes-types-structures and processing prototypes-mechanisms.

*bar_types.h, bar_types.cpp* have
  template< typename float_type_typename = float > struct bar_type;
  typedef bar_type< float > float_bar_type;
  typedef bar_type< double > double_bar_type;

*signal_types.h, signal_types.cpp* have
  signal_type - open, close
  class signal - signal prototype (abstract class)
  struct close_signal : public signal
  struct open_signal : public signal - long, short

