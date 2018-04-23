function y = losses(x, mrtl)
if x <= mrtl
    y = (mrtl-x).*20;
else
    y = (x-mrtl).*50;
end