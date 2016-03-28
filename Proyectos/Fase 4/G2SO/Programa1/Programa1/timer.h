//Se utiliza una API- Propia de Windows la cual permite hacer timers asíncronos.
//BOOL WINAPI CreateTimerQueueTimer(
//ES un puntero a un HANDLE estándar de Windows (PHANDLE)
//  _In_opt_  HANDLE TimerQueue, //TimerQueue permite emplear colas de timers “custom”.
//  _In_      WAITORTIMERCALLBACK Callback, //Define un tipo de función a la que el sistema operativo invocará al dispararse el temporizador.
//  _In_opt_  PVOID Parameter, //Argumento que se pasará de vuelta al Callback
//  _In_      DWORD DueTime, // Tiempos para el primer disparo y siguientes
//  _In_      DWORD Period, //Periodo entre cada tiempo
//);


//El timer se ejecutará de forma asíncrona, en un hilo controlado por el sistema operativo.
#pragma once

#include <functional>

//Clase para el temporizador
class CTimer
{
public:
  CTimer()
  {
    m_hTimer = NULL;//inicializa el constructor de la clase
  }
  virtual ~CTimer()
  {
    Cancel(); // Destruye el timer junto con nuestro objeto
  }

public:
  HRESULT Set(DWORD dueTime,std::function<void()> callback)
  {
    return(Set(dueTime,0,callback));
  }

 //Configuración del timer. Crea o alterna dependiendo si m_htimer tiene un valor.
  HRESULT Set(DWORD dueTime,DWORD period,std::function<void()> callback)
  {
    if (m_hTimer == NULL)
    {
      if (CreateTimerQueueTimer(&m_hTimer,NULL,&internalCallback,this,  //permite recibir la notificación del SO para saber cual invocar.
      dueTime,period,
      period ? WT_EXECUTEDEFAULT : WT_EXECUTEONLYONCE) == FALSE)
      return(GetLastError());
    }
    else
    {
      if (ChangeTimerQueueTimer(NULL,m_hTimer,dueTime,period) == FALSE)
        return(GetLastError());
    }
    m_callback = callback; //se almacena la expresión que se quiere emplear, permitiendo emplear el mismo timer con diferentes funciones.
    return(S_OK);
  }

  //Destruye el timer. 
  HRESULT Cancel()
  {
    if (m_hTimer != NULL)
    {
      DeleteTimerQueueTimer(NULL,m_hTimer,NULL); //elimina el timer creado con CreateTimerQueueTimer()
      m_hTimer = NULL; //asigna valor null a la variable.
    }
    return(S_OK);
  }

private:
  static VOID CALLBACK internalCallback(PVOID lpParameter,BOOLEAN TimerOrWaitFired)
  {
    CTimer *pTimer = (CTimer*)lpParameter; //casteamos el parametro timer. Devuelve el puntero para utilizarlo para determinar el contenido de la función.
    if (pTimer->m_callback)
      pTimer->m_callback();
  }

private:
  HANDLE m_hTimer; //devolvera el valor al crear el timer
  std::function<void()> m_callback; //almacena la expresion lambda
};
