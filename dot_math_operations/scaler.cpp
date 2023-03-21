#include "scaler.h"

error_category_t scale_dot(dot_t &dot, dot_t &center, scaler_t &scaler)
{
	error_category_t rc = OK;
	if (fabs(scaler.kx) < EPS || fabs(scaler.ky) < EPS || fabs(scaler.kz) < EPS)
		rc = INVALID_SCALER;
	if (rc == OK)
	{
		dot.x = (dot.x - center.x) * scaler.kx + center.x;
		dot.y = (dot.y - center.y) * scaler.ky + center.y;
		dot.z = (dot.z - center.z) * scaler.kz + center.z;
	}
	return rc;
}

error_category_t scale_dots(dot_array &array, dot_t &center, scaler_t &scaler)
{
	error_category_t rc = OK;
	for (int i = 0;  rc == OK && i < array.len; i++)
		rc = scale_dot(array.dots[i], center,scaler);
	return rc;

}
