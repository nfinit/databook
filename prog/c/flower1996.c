/* Stellar characterization procedures for deriving bolometric corrections
 * and effective temperatures from B-V index based on methods presented by
 * Phillip Flower with coefficient corrections provided by Guillermo Torres
 */

#include <math.h>

/* Bolometric correction coefficients for log Teff < 3.70 */
#define BCA1 -0.190537291496456E+05
#define BCB1  0.155144866764412E+05
#define BCC1 -0.421278819301717E+04
#define BCD1  0.381476328422343E+03

/* Bolometric correction coefficients for log Teff < 3.90 */
#define BCA2 -0.370510203809015E+05
#define BCB2  0.385672629965804E+05
#define BCC2 -0.150651486316025E+05
#define BCD2  0.261724637119416E+04
#define BCE2 -0.170623810323864E+03

/* Bolometric correction coefficients for log Teff > 3.90 */
#define BCA3 -0.118115450538963E+06
#define BCB3  0.137145973583929E+06
#define BCC3 -0.636233812100225E+05
#define BCD3  0.147412923562646E+05
#define BCE3 -0.170587278406872E+04
#define BCF3  0.788731721804990E+02

/* Effective temperature function coefficients for typical stars */
#define VA    3.979145106714099
#define VB   -0.654992268598245
#define VC    1.740690042385095
#define VD   -4.608815154057166
#define VE    6.792599779944473
#define VF   -5.396909891322525
#define VG    2.192970376522490
#define VH   -0.359495739295671

/* Effective temperature function coefficients for supergiants */
#define SA    4.012559732366214
#define SB   -1.055043117465989
#define SC    2.133394538571825
#define SD   -2.459769794654992
#define SE    1.349423943497744
#define SF   -0.283942579112032

/* Function prototypes */
double bcv(double t);
double bv2lt(double bv);
double bv2bcv(double bv);

/* Bolometric correction constant given temperature (kelvin)
 */
double bcv(double t)
{
	double logt;
	logt = log(t);
	if (logt < 3.70) {
		return BCA1+(BCB1*logt)+(BCC1*pow(logt,2))+(BCD1*pow(logt,3));
	} else if (logt < 3.90) {
		return BCA2+(BCB2*logt)+(BCC2*pow(logt,2))+(BCD2*pow(logt,3))+(BCE2*pow(logt,4));
	} else {
		return BCA3+(BCB3*logt)+(BCC3*pow(logt,2))+(BCD3*pow(logt,3))+(BCE3*pow(logt,4))+(BCF3*pow(logt,5));
	}
}
