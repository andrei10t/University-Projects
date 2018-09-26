function z = zigzag(n)
  A = zeros(n);
  i=1;
  j=1;
  %pun 0-ul
  A(i,j)=0;
  k=1;
  % caz 1-> n impar
  if(mod(n,2)==1)
  %cat timp nu am pus ultimul numar
    while(k<=n*n)
    %cand merg la dreapta
      if( (i==1 && mod(j,2)==1 && j<n) || (i==n && mod(j,2)==0) && j<n)
        j=j+1;
	      A(i,j)=k;
	      k=k+1;
      endif
      %cand merge in jos
      if( (j==1 && mod(i,2)==0 && i<n) || (j==n && mod(i,2)==1) && i<n)      
        i=i+1;
	      A(i,j)=k;
	      k=k+1;
      endif
      %cand merge jos-stanga
      if(mod(i+j,2)==1 && j!=1)
        i=i+1;
	      j=j-1;
        A(i,j)=k;
        k=k+1;
      endif
      %cand merge sus dreapta
      if(mod(i+j,2)==0 && i!=1)
        i=i-1;
        j=j+1;
	      A(i,j)=k;
        k=k+1;
      endif
    endwhile
  endif
  % caz 2
  if(mod(n,2)==0)
  %cat timp nu am pus ultimul numar
    while(k<=n*n)
    %cand merg la dreapta
      if( (i==1 && mod(j,2)==1) || (i==n && mod(j,2)==1) )
        j=j+1;
	      A(i,j)=k;
	      k=k+1;
      endif
      %cand merge in jos
      if( (j==1 && mod(i,2)==0 && i<n) || (j==n && mod(i,2)==0) && i<n)      
        i=i+1;
	      A(i,j)=k;
	      k=k+1;
      endif
      %cand merge jos-stanga
      if(mod(i+j,2)==1 && j!=1)
        i=i+1;
	      j=j-1;
        A(i,j)=k;
        k=k+1;
      endif
      %cand merge sus-dreapta
      if(mod(i+j,2)==0 && i!=1)
        i=i-1;
        j=j+1;
	      A(i,j)=k;
        k=k+1;
      endif
    endwhile
  endif  
  [n,m]=size(A);
  A=A(1:n,1:m-1);
  disp(A)
      
endfunction