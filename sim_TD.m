function [T1, T2] = sim_TD(x, y, v, c, eps)
   T1 = (sqrt(x^2 + y^2) / v) + (sqrt((x - c)^2 + y^2) / v) + eps;
   T2 = (sqrt(x^2 + y^2) / v) + (sqrt((x + c)^2 + y^2) / v) + eps;
end
