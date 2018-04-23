function str = num2sip(val,sgf,pfx,trz)
% Convert a scalar numeric into an SI prefixed string. (metric/engineering)
%
% (c) 2015 Stephen Cobeldick
%
% ### Function ###
%
% Convert a scalar numeric value into a string. The value is shown in the string
% as a coefficient with an SI unit prefix, such that 1<=coefficient<1000. If the
% rounded |val|<10^-24 or |val|>=10^27 then E-notation is used, without a prefix.
%
% Syntax:
%  str = num2sip(val)
%  str = num2sip(val,sgf)
%  str = num2sip(val,sgf,pfx)
%  str = num2sip(val,sgf,pfx,trz)
%
% See also SIP2NUM NUM2BIP BIP2NUM NUM2STR STR2NUM MAT2STR SSCANF SPRINTF NUM2WORDS WORDS2NUM NATSORT NATSORTFILES
%
% ### Examples ###
%
% num2sip(10000)  OR  num2sip(1e4)
%  ans = '10 k'
% num2sip(10000,4,true)
%  ans = '10 kilo'
% num2sip(10000,4,false,true)
%  ans = '10.00 k'
%
% num2sip(999,2)
%  ans = '1 k'
% num2sip(999,3)
%  ans = '999 '
%
% num2sip(-5.555e9,3)
%  ans = '-5.56 G'
%
% ['Power: ',num2sip(200*1000^2,[],true),'watt']
%  ans = 'Power: 200 megawatt'
%
% sprintf('Clock frequency is %shertz.',num2sip(1234567890,8,true))
%  ans = 'Clock frequency is 1.2345679 gigahertz.'
%
% num2sip(sip2num('9 T'))
%  ans = '9 T'
%
% ### SI Prefix Strings ###
%
% Order  |1000^1 |1000^2 |1000^3 |1000^4 |1000^5 |1000^6 |1000^7 |1000^8 |
% -------|-------|-------|-------|-------|-------|-------|-------|-------|
% Name   | kilo  | mega  | giga  | tera  | peta  | exa   | zetta | yotta |
% -------|-------|-------|-------|-------|-------|-------|-------|-------|
% Symbol*|   k   |   M   |   G   |   T   |   P   |   E   |   Z   |   Y   |
%
% Order  |1000^-1|1000^-2|1000^-3|1000^-4|1000^-5|1000^-6|1000^-7|1000^-8|
% -------|-------|-------|-------|-------|-------|-------|-------|-------|
% Name   | milli | micro | nano  | pico  | femto | atto  | zepto | yocto |
% -------|-------|-------|-------|-------|-------|-------|-------|-------|
% Symbol*|   m   |   u   |   n   |   p   |   f   |   a   |   z   |   y   |
%
% ### Input & Output Arguments ###
%
% Inputs (*==default):
%  val = NumericScalar, the value to be converted to string <str>.
%  sgf = NumericScalar, the significant figures in the coefficient, *5.
%  pfx = LogicalScalar, true/false* -> select SI prefix as name/symbol.
%  trz = LogicalScalar, true/false* -> select if decimal trailing zeros are required.
%
% Output:
%  str = Input <val> as a string: coefficient + space character + SI prefix.
%
% str = num2sip(val,*sgf,*pfx,*trz)

% ### Input Wrangling ###
%
if nargin<4
	trz = false;
else
	assert(islogical(trz)&&isscalar(trz),'Fourth input <trz> must be a logical scalar.')
end
if nargin<3
	pfx = false;
else
	assert(islogical(pfx)&&isscalar(pfx),'Third input <pfx> must be a logical scalar.')
end
if nargin<2 || isnumeric(sgf)&&isempty(sgf)
	sgf = 5;
else
	assert(isnumeric(sgf)&&isscalar(sgf),'Second input <sgf> must be a numeric scalar.')
	sgf = double(uint8(sgf));
end
assert(isnumeric(val)&&isscalar(val)&&isreal(val),'First input <val> must be a real numeric scalar.')
val = double(val);
%
if trz && sgf>1
	fmt = '%#.*g %s';
else
	fmt = '%.*g %s';
end
%
% ### Generate String ###
%
if isfinite(val)
	% Calculate coefficient value:
	xpt = rem(min(9,max(-9,[0;1]+floor(log10(abs(val))/3))),9);
	cof = val.*1000.^-xpt;
	% Round coefficient value:
	ord = 1+floor(log10(abs(cof)));
	if val~=0
		cof = 10.^(ord-sgf).*round(cof.*10.^(sgf-ord));
	end
	% Select prefix symbol/name:
	pfc = {'yocto','zepto','atto','femto','pico','nano','micro','milli','','kilo','mega','giga','tera','peta','exa','zetta','yotta';...
	       'y',    'z',    'a',   'f',    'p',   'n',   'u',    'm',    '','k',   'M',   'G',   'T',   'P',   'E',  'Z',    'Y'};
	idx = 1+any(abs(cof)==[1000;1]);
	pfs = pfc{2-pfx,9+xpt(idx)};
	% Convert to string (without prefix || whole part<digits):
	if 4<abs(ord(idx)) || floor(1+log10(abs(cof(idx))))<sgf
		str = sprintf(fmt,sgf,cof(idx),pfs);
	else % (whole part>=digits)
		str = sprintf('%.0f %s',cof(idx),pfs);
	end
else
	str = sprintf('%f ',val);
end
%
end
%----------------------------------------------------------------------END:num2sip