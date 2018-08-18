#pragma once
class Cell
{
	int _x, _y;
	bool _passable;
public:
	Cell();
	Cell(int x, int y);
	Cell(int x, int y, bool passable);
	~Cell();

	int get_x() const;
	inline void set_x(int x);

	int get_y() const;
	inline void set_y(int y);

	bool get_passable() const;
	void set_passable(bool new_value);

	bool operator==(Cell) const;
	bool operator!=(Cell cell) const;
	size_t operator()(Cell const& x) const noexcept;
};

