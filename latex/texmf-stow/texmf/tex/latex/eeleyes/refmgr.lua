local M = {}

M.reference_table = {
    lookup = {},
    stack = {},
}

---@param label string
function M.push_stack(label)
    M.reference_table.stack[#M.reference_table.stack + 1] = label
end

---@param match string|nil
---@return string|nil
function M.pop_stack(match)
    if match == nil or M.reference_table.stack[#M.reference_table.stack] == match then
        return table.remove(M.reference_table.stack)
    end

    return nil
end

---@param label string
function M.to_proof_namespace(label)
    return label:gsub("^%w-:", "pf:")
end

---@param label string
---@param name string
function M.add_ref(label, name)
    M.reference_table.lookup[label] = name
end

---@param label string
function M.search_ref(label)
    return M.reference_table.lookup[label]
end

return M
