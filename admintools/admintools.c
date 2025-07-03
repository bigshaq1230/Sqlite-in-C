#include "gerer_service.c"
#include "gerer_patient.c"
#include "gerer_medcin.c"
#include "gerer_holidays.c"
#include "gerer_cons.c"
void home();
void admintools();
void admintools()
{
    switch (option("1)gerer les services 2)gerer les medecins 3)gerer les patients 4)gerer les consultation 5)gerer les jour ferier 0)return"))
    {
    case 1:
        gerer_les_services();
        admintools();
        break;
    case 2:
        gerer_les_medecins();
        admintools();
        break;
    case 3:
        gerer_les_patients();
        admintools();
        break;
    case 4:
        planifier_les_redez_vous();
        admintools();
        break;
    case 5:
        gerer_holidays();
        admintools();
        break;
    case 0:
        home();
        break;
    default:
        break;
    }
}
