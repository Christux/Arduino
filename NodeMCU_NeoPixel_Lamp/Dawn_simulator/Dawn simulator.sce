/*
 * Copyright (c) 2017 Christophe Rubeck.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

xdel(winsid());
clear('all');

Dt=30*60; // 3à minutes in seconds
Imax=1; // or 255 for 8 bits
k=0.4;
t=0:0.1:Dt;

R=1 ./  (1+exp(-0.4*30/Dt*(t-Dt*0.67)));
G=0.7 ./ (1+exp(-0.5*30/Dt*(t-Dt*0.7)));
B=0.1 ./ (1+exp(-0.6*30/Dt*(t-Dt*0.8)));

plot(t/60,Imax*R, 'color', 'red','LineWidth',3);
plot(t/60,Imax*G, 'color', 'green','LineWidth',3);
plot(t/60,Imax*B, 'color', 'blue','LineWidth',3);

legend(['Red','Green','Blue'],[2]);
xgrid(1);
xlabel('Time (min)');
ylabel('Intensity');
title('Christux dawn simulator');
