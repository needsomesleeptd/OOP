//
// Created by Андрей on 29.05.2023.
//

#ifndef INC_3_LAB_3_INC_UTILS_BASETRANSFORMER_H_
#define INC_3_LAB_3_INC_UTILS_BASETRANSFORMER_H_



class BaseTransformer
{
 public:
	BaseTransformer() = default;
	BaseTransformer(const double x, const double y, const double z);
	BaseTransformer(const BaseTransformer &AbstractTransformer) = default;
	BaseTransformer(const BaseTransformer &&AbstractTransformer) noexcept;
	~BaseTransformer() = default;

	void move  (const double dx, const double dy, const double dz);
	void scale (const double kx, const double ky, const double kz);
	void rotate(const double ox, const double oy, const double oz);

	double get_x() const;
	double get_y() const;
	double get_z() const;

	void set_x(double const &x);
	void set_y(double const &y);
	void set_z(double const &z);

	bool operator == (const BaseTransformer &AbstractTransformer) const noexcept;
	bool operator != (const BaseTransformer &AbstractTransformer) const noexcept;
	bool is_equal    (const BaseTransformer &AbstractTransformer) const noexcept;
	bool is_not_equal(const BaseTransformer &AbstractTransformer) const noexcept;

	BaseTransformer &operator = (const BaseTransformer &AbstractTransformer) = default;
	BaseTransformer &operator = (BaseTransformer &&AbstractTransformer) noexcept;
	BaseTransformer  operator + (const BaseTransformer &AbstractTransformer);
	BaseTransformer  operator - (const BaseTransformer &AbstractTransformer);
 private:
	double _x;
	double _y;
	double _z;

};


#endif //INC_3_LAB_3_INC_UTILS_BASETRANSFORMER_H_
