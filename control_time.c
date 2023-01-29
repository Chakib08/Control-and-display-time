#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>


char c;
  int heure[3];
  int param = 0;

/*La fonction timer_real() est appélé avec la fonction settimer() chaque seconde (configuration des parametres du timer)*/

void timer_real (int signum)
{


  affiche_heure (heure);
  heure[2]++;

}


void affiche_heure (int *);

int main (void)
{


  heure[0] = 0; //heures
  heure[1] = 0; //minutes
  heure[2] = 0; //secondes


  printf ("Pressez P pour augmenter\n");
  printf ("Pressez M pour diminuer\n");
  printf ("Pressez Espace pour changer de parametre\n");


 
  volatile unsigned int i,j=0;
struct sigaction sar;
struct itimerval timer;

  /* Configure timer_real comme routine d'interruption du signal SIGALRM.  */
  memset (&sar, 0, sizeof (sar));
  sar.sa_handler = &timer_real; // pour l'utilisation de la fonction timer_real chaque seconde avec le timer on affcete l'adresse de la fonction timer_real au parametre sa_handler
  sigaction (SIGALRM, &sar, NULL);

  /* Configure les timers pour une durée initiale de 1 seconde...  */
  timer.it_value.tv_sec = 1;
  timer.it_value.tv_usec = 0;
  /* ... et 1 seconde pour les suivantes.  */
  timer.it_interval.tv_sec = 1;
  timer.it_interval.tv_usec = 0;
  


  /* Démarre un timer reel. Il compte le temps écoulé pour le process courant.  */
  setitimer (ITIMER_REAL, &timer, NULL);


  
  while (1)
	{


	  if (heure[2] > 59)  //secondes > 59
	    {
	      heure[2] = 0; //secondes = 0;
	      heure[1]++;  // minute++
	    }
	  if (heure[1] > 59) //minute>59
	    {
              heure[1] = 0; //minutes = 0
	      heure[0]++;  //heure++
	    }
	  if (heure[0] > 23) //heure > 23
	  {
	      heure[0] = 0; //heure = 0
              
	  }

if (heure[2] < 0) // secondes < 0
	    {
	      heure[2] = 59; //secondes  59 00:00:00 ==> 23:59:59
	      heure[1]--;    //minutes--
	    }
	  if (heure[1] < 0) // minutes < 0
	    {
		heure[1] = 59; //minutes = 59
                heure[0]--; //heures--
	    }
	  if (heure[0] < 0) //heures < 0
	  {
		heure[0] = 23; //heures = 23
                
	  }

      c = getchar ();
      switch (c)
	{
	case 'p':
	  heure[param]++;
	  break;

	case 'm':
	  heure[param]--;
	
	  break;

	case ' ':
	  param++;
	  if (param > 2)
	    param = 0;
	  printf ("parametre=%d ", param);
	  break;

	default:
	  break;

		}




	}
  return(EXIT_SUCCESS); // jamais executé
}

void affiche_heure (int *heure)
{

  printf ("%02d:%02d:%02d\n", heure[0], heure[1], heure[2]); // affichage de heure : minute : seconde
  return;
}
