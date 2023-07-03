#!/bin/bash
echo "Input 'usage' for help"
# 循环读取指令
while read -p "Input command: " cmd args; do
    # 解析命令
    case "$cmd" in
        "usage")
            ./diary usage
            # 执行显示用法的操作
            ;;
        "add")
            if [ -z "$args" ]
            then
                echo "Error: No filename specified"
                exit 1
            fi
            ./diary add "$args"
            # 执行添加日记的操作
            ;;
        "show")
            if [ -z "$args" ]
            then
                echo "Error: No filename or date specified"
                exit 1
            fi
            filename=$(echo "$args" | cut -d " " -f 1)
            date=$(echo "$args" | cut -d " " -f 2)
            ./diary show "$filename" "$date"
            # 执行显示日记的操作
            ;;
        "remove")
            if [ -z "$args" ]
            then
                echo "Error: No filename or date specified"
                exit 1
            fi
            filename=$(echo "$args" | cut -d " " -f 1)
            date=$(echo "$args" | cut -d " " -f 2)
            ./diary remove "$filename" "$date"
            # 执行删除日记的操作
            ;;
        "list")
            IFS=' ' read -ra args_array <<< "$args"
            args_count=${#args_array[@]}
            if [ "$args_count" -eq 0 ]
            then
                echo "Error: No filename specified"
                exit 1
            fi
            filename=$(echo "$args" | cut -d " " -f 1)
            start_date=$(echo "$args" | cut -d " " -f 2)
            end_date=$(echo "$args" | cut -d " " -f 3)
            if [ "$args_count" -eq 1 ]
            then
                ./diary list "$filename"
            elif [ "$args_count" -eq 2 ]
            then
                ./diary list "$filename" "$start_date"
            else
                ./diary list "$filename" "$start_date" "$end_date"
            fi
            #列出指定范围的日记

            ;;
        "quit")
            echo "Good Bye"
            exit 0
            ;;
        *)
            echo "Invalid command"
            exit 1
            ;;
    esac
done