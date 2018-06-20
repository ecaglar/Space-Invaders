#pragma once
class Rect
{
public:
	
	Rect(void);
	Rect(double, double, double, double);
	~Rect(void);

	double Get_Buttom_right_y() const { return buttom_right_y; }
	void Set_Buttom_right_y(double val) { buttom_right_y = val; }
	double Get_Buttom_right_x() const { return buttom_right_x; }
	void Set_Buttom_right_x(double val) { buttom_right_x = val; }
	double Get_Toop_left_y() const { return toop_left_y; }
	void Set_Toop_left_y(double val) { toop_left_y = val; }
	double Get_Top_left_x() const { return top_left_x; }
	void Set_Top_left_x(double val) { top_left_x = val; }

private:
	double top_left_x, toop_left_y, buttom_right_x, buttom_right_y;


};

