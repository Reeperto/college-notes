local Mgr = {
    labels = {},
    envs = {},
}

function Mgr.init_env(name)
    Mgr.envs[name] = {}
end

function Mgr.env_add(env_name, name)
    Mgr.envs[env_name][name] = true
end

function Mgr.env_has_name(env_name, name)
    return Mgr.envs[env_name][name] ~= nil
end

function Mgr.push_label(label)
    Mgr.labels[#Mgr.labels+1] = label
end

function Mgr.peek_label()
    if #Mgr.labels > 0 then
        return Mgr.labels[#Mgr.labels]
    else
        return ""
    end
end

function Mgr.pop_label()
    if #Mgr.labels > 0 then
        table.remove(Mgr.labels, #Mgr.labels)
    end
end

---@param label string
---@return string
function Mgr.label_as_proof(label)
    local modified = label:gsub("^[^:]+:", "pf:")
    return modified
end

_G.Mgr = Mgr
