#include "SlowDownAllStrategy.h"


SlowDownAllStrategy::SlowDownAllStrategy() : AttackStrategy()
{

}

bool SlowDownAllStrategy::attack(std::vector<Enemy*>& targets)
{
    //Inflige 0.5 points de dégats à la première cible disponible

    if (!targets.empty())
    {
        //On slow tous les ennemis possibles
        for (int i = 0; i < targets.size(); i++)
        {
            //On vérifie que la vitesse de l'ennemi n'est pas déjà modifiée
            if (targets[i]->getSpeed() == targets[i]->getOriginSpeed())
            {
                // On modifie et on appelle reload movement pour appliquer la nouvelle vitesse au vecteur de déplacement  
                targets[i]->setSpeed(targets[i]->getOriginSpeed()/2);
                targets[i]->reloadMovement();
            }
            

        }
        

    }

    return false;
}