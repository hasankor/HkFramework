#include "toastmanager.h"

ToastManager::ToastManager(QObject *parent)
    : QObject(parent)
{

}

ToastManager *ToastManager::getInstance(){
    static ToastManager toastManager;
    return &toastManager;
}

