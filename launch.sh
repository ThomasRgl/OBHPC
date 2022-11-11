echo "### stability ###"
cd stability 
bash ./launch.sh

echo "### latency ###"
cd ../latency
bash ./launch.sh

echo "### degemm ###"
cd ../dgemm
bash ./launch.sh

echo "### reduc ###"
cd ../reduc
bash ./launch.sh

echo "### dotprod ###"
cd ../dotprod
bash ./launch.sh
