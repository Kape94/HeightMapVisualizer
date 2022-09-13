#ifndef _CONTEXT_H
#define _CONTEXT_H

namespace Context {
  using Callback = void(*)();

  void Create(
    const unsigned width, 
    const unsigned height, 
    Callback init, 
    Callback render
  );

  void SetMouseMotionFunc(void(*motionFunc)(int, int));
  void SetKeyboardFunc(void(*keyboardFunc)(unsigned char));

  void Run();
  void Exit();
}

#endif 
