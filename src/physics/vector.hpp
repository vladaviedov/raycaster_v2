#ifndef RC2_PHYSICS_VECTOR_HPP
#define RC2_PHYSICS_VECTOR_HPP

class Vector {
	private:
		Vector(double x, double y);

		void round();

		double x;
		double y;
	public:
		~Vector();

		static Vector make_cart(double x, double y);
		static Vector make_polar(double r, double th);
		static Vector *new_cart(double x, double y);
		static Vector *new_polar(double r, double th);

		double get_x();
		double get_y();
		double get_r();
		double get_th();

		void set_cart(double x, double y);
		void set_polar(double r, double th);

		void apply_to(Vector &vec, double mult);
};

#endif // RC2_PHYSICS_VECTOR_HPP
