/*
Version: 0.0.1
Created by Jacob Schroeder
(c) Copyright 2017 by Retro Moon Softworks. All Rights Reserved.
*/

#include <windows.h>

LRESULT CALLBACK
MainWindowCallback(HWND Window,
                   UINT Message,
                   WPARAM WParam,
                   LPARAM LParam)
{
  LRESULT Result = 0;

  switch(Message)
  {
    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE\n");
    } break;

    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY\n");
    } break;

    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE\n");
    } break;

    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;

    case WM_PAINT:
    {
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(Window, &Paint);
      int X = Paint.rcPaint.left;
      int Y = Paint.rcPaint.top;
      int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
      int Width = Paint.rcPaint.right - Paint.rcPaint.left;
      PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
      EndPaint(Window, &Paint);
    } break;

    default:
    {
    //  OutputDebutStringA("default\n");
      Result = DefWindowProc(Window, Message, WParam, LParam);
    } break;
  }

  return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CommandLine,
        int ShowCode)
{
  WNDCLASS WindowClass = {};
  WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallback;
  WindowClass.hInstance = Instance;
//  WindowClass.hIcon = ;
  WindowClass.lpszClassName = "NyxWindowClass";

  if(RegisterClass(&WindowClass))
  {
    HWND WindowHandle = CreateWindowEx(0,
                                       WindowClass.lpszClassName,
                                       "Nyx Engine",
                                       WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                       CW_USEDEFAULT,
                                       CW_USEDEFAULT,
                                       CW_USEDEFAULT,
                                       CW_USEDEFAULT,
                                       0,
                                       0,
                                       Instance,
                                       0);
    if(WindowHandle)
    {
      MSG Message;
      for(;;)
      {
        BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
        if(MessageResult > 0)
        {
          TranslateMessage(&Message);
          DispatchMessage(&Message);
        }
        else
        {
          break;
        }
      }
    }
    else
    {
      // TODO(Jacob): Logging
    }
  }
  else
  {
    // TODO(Jacob): Logging
  }

  return(0);
}
