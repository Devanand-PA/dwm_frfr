cd(){
	[ "$new_dir" != "$(pwd)" ] && olddir="$(pwd)"
	command cd "$@"
}

j_n(){
	new_dir="$(find -type d | xargs realpath | fzf --height=10%)"
	echo "$new_dir" >> ~/.newdirs
	cd "$new_dir"
}

j(){
	new_dir="$(cat ~/.newdirs | xargs realpath | fzf --height=10%)"
	cd "$new_dir"
}

k() {
if [ "$olddir" ] 
then
	new_dir="$olddir"
	cd "$new_dir"
fi
}
