#ifndef GESTIONHAPTIQUE_H
#define GESTIONHAPTIQUE_H


//Compilation en mode non unicode
#undef UNICODE



#include <ifc.h>
#include <QPoint>
#include <QMainWindow>

class Story;

class GestionHaptique
{
public:
    GestionHaptique(Story *fen);
    ~GestionHaptique();

    CImmCompoundEffect *GetHeartBoomMesCouilles() const;
    CImmCompoundEffect *GetEarthquakeMesCouilles() const;
    CImmProject *GetProjet() const;
private:
    CImmMouse *mSouris;
    CImmProject  *mProjet;
    CImmCompoundEffect	*mHeartBoomMesCouilles;
    CImmCompoundEffect	*mEarthquakeMesCouilles;
    Story *mFenetre;
};


#endif // GESTIONHAPTIQUE_H

