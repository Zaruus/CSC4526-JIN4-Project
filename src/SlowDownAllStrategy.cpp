#include "SlowDownAllStrategy.h"


SlowDownAllStrategy::SlowDownAllStrategy() : AttackStrategy()
{

}

bool SlowDownAllStrategy::attack(std::vector<Enemy*>& targets)
{
    //Inflige 0.5 points de d�gats � la premi�re cible disponible

    if (!targets.empty())
    {
        //On slow tous les ennemis possibles
        for (int i = 0; i < targets.size(); i++)
        {
            //On v�rifie que la vitesse de l'ennemi n'est pas d�j� modifi�e
            if (targets[i]->getSpeed() == targets[i]->getOriginSpeed())
            {
                // On modifie et on appelle reload movement pour appliquer la nouvelle vitesse au vecteur de d�placement  
                targets[i]->setSpeed(targets[i]->getOriginSpeed()/2);
                targets[i]->reloadMovement();
            }
            

        }
        

    }

    return false;
}