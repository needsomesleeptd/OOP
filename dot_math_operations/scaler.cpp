#include "scaler.h"

error_category_t scale_dot(dot_t &dot, scaler_t &scaler)
{
	error_category_t rc = OK;
	if (fabs(scaler.kx) < EPS && fabs(scaler.ky) < EPS && fabs(scaler.kz) < EPS)
		rc = INVALID_SCALER;
	if (rc == OK)
	{
		dot.x *= scaler.kx;
		dot.y *= scaler.ky;
		dot.z *= scaler.kz;
	}
	return rc;
}

error_category_t scale_dots(dot_array &array, scaler_t &scaler)
{
	error_category_t rc = OK;
	for (int i = 0;  rc == OK && i < array.len; i++)
		rc = scale_dot(array.dots[i],scaler);
	return rc;

}
